#pragma once

#include "../engine_plugin_api/plugin_c_api.h"
#include "hash_map.h"
#include "random.h"

namespace stingray_plugin_foundation
{
	inline EntityRef nil_entity() { return 0u; }
	inline Instance nil_instance() { return 0u; }
	inline bool is_some_instance(Instance i) { return i != 0; }
	inline bool is_nil_instance(Instance i) { return i == 0; }
	inline InstanceId nil_instance_id() { return 0u; }

	// This is a base class for implementing a C++ style entity component
	// Use this if you want total control of instance management.
	class EntityComponent
	{
		const unsigned _marker;
		public:
			virtual ~EntityComponent();

			bool marker_valid() const { return _marker == COMPONENT_MARKER; }

			// Set up the api to use callbacks into an EntityComponent instance
			static void setup_api(ComponentApi &api);
		protected:
			EntityComponent();

			//////// EntityComponent API - callbacks for the ComponentApi base functionality
			virtual Instance create(EntityRef entity, InstanceId instance_id) = 0;
			virtual void destroy(Instance i) = 0;
			virtual void destroy_all(EntityRef entity) = 0;
			virtual Instance lookup_instance(EntityRef entity, InstanceId id) const = 0;
			virtual EntityInstanceId lookup_instance_id(Instance instance) const = 0;
			virtual void spawn(const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data) = 0;
			virtual void set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices) = 0;
			virtual void spawned(const EntityRef *entities, unsigned num_entities) = 0;
			virtual Instance first_instance(EntityRef entity) const = 0;
			virtual Instance next_instance(InstanceId instance) const = 0;

		private:
			static const int COMPONENT_MARKER = 0x21a4cb82;
			static EntityComponent& cast(ComponentPtr component);
	};

	// This is the interface a garbage collected component manager implementation needs to provide.
	// It is the same interface to implement regardless if it is a single (SingleInstanceEntityComponent)
	// or multi (MultiInstanceEntityComponent) instance implementation.
	class IGCEntityComponent {
		public:
			// Read the instance `i` associated with entity `entity` with id `instance_id` resource data and perform any initialziation needed when
			// spawned from a resource.
			//
			//     Example:
			//     {
			//         // Read the resource data
			//         _spin[instance] = *(float*)data;
			//         data += sizeof(float);
			//         _length[instance] = *(uint32_t*)data;
			//         data += sizeof(uint32_t);
			//     }
			virtual void spawn_instance(EntityRef entity, Instance i, InstanceId instance_id, const char *&data) = 0;

			// Set the parent entity for entities
			//     entities - List of entities to set parent/child relationships for
			//     num_entities - number of entities to modify
			//     parent_indices - List of the same length as the entity list of parent indices. Use nil_instance_id as an index for an entity that has no parent.
			virtual void entity_set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices) = 0;

			// Callback when all the component instances for the entities has been spawned
			//     entities - array of entities that has been completely spawned (all components for the entity has been created)
			//     num_entities - number of entities
			virtual void instances_spawned(const EntityRef *entities, unsigned num_entities) = 0;

			// Initialize component specific data for instance `i` with your default data
			//     Example:
			//     {
			//         _spin[i] = -1.f;
			//         _length[i] = 256;
			//     }
			virtual void create_instance(Instance i) = 0;

			// Release any referenced data the instance i might be associated with and reset the instance fileds
			//
			//     Example:
			//     {
			//         _spin[i] = 0.f;
			//         _length[i] = 0;
			//     }
			virtual void destroy_instance(Instance i) = 0;

			// If your component manager references the instance `from` it needs to change that reference to instance `to`
			//
			//     Example:
		    //     {
			//         if (from == my_special_instance)
			//             my_special_instance = to;
			//     }
			virtual void change_instance_references(Instance to, Instance from) = 0;

			// Move the component specific data from instance `from` to `to`. `from` should be dispose as if
			// destroy_component(from) was called
			//
			//     Example:
			//     {
			//         _spin[to] = _spin[from];
			//         _length[to] = _length[from];
			//         _spin[from] = 0.f;
			//         _length[from] = 0;
			//     }
			virtual void move_instance_data(Instance to, Instance from) = 0;

			// Return the size of your custom data (size per instance)
			//
			//     Example:
			//     {
			//         return sizeof(float) + sizeof(uint32_t);
			//     }
			virtual unsigned instance_total_field_size() = 0;

			// Initialize your custom instance data field pointers and copy data from the (optional) current data pointers.
			// Easiest accomplished using the copy_field template method provided.
			//
			//     Example:
			//
			//     {
			//         _spin = copy_field(to, to_capacity, _spin, from_capacity);
			//         _length = copy_field(to, to_capacity, _length, from_capacity);
			//     }
			virtual void copy_component_fields(char *to, unsigned to_capacity, unsigned from_capacity) = 0;

		protected:
			virtual ~IGCEntityComponent() {}
	};


	// This is the base class that provide garbage collection for instances
	// and is used to implement the SingleInstanceEntityComponent and MultiInstanceEntityComponent.
	//
	// You normally use SingleInstanceEntityComponent or MultiInstanceEntityComponent but you
	// have the option to base your component on this if you so choose.
	//
	// The subclass needs to implement the IGCEntityComponent interface.
	//
	// The base GCEntityComponent handles the basic functionalities of a entity component
	// mananger implementation - mapping entities to instances and doing garbage collection sweeps.
	//
	// Your sub-class needs to manage the destruction of all non-gc:d instances at the destructor
	// since only the memory allocated for the instances will be freed - reclaim() will not be
	// called for any instances in the component destructor.
	//
	// Add data fields for your instances by adding pointer to arrays in a SOA pattern in your subclass.
	//
	// Example
	//     // If each instance has a float "_spin" field and a uint32_t "_length" field it would be declared
	//     // as the following in your subclass, remember to initialize them to nullptr in you constructor.
	//
	//     float *_spin;
	//     uint32_t *_length;
	//
	//     // You also need to allocate a base count of instances in your subclass constructor by calling "allocate"
	//
	//     allocate(16);	// Reserves an initial capacity of 16 instances
	//

	class GCEntityComponent : public EntityComponent, protected IGCEntityComponent
	{
		public:
			virtual ~GCEntityComponent();

			// Incrementally destroy instances whose entities have been destroyed.
			void garbage_collect_entities();

			// Incrementally reclaim destroyed instances.
			void garbage_collect_instances();

		protected:
			GCEntityComponent(Allocator &allocator, EntityManagerApi* entity_manager);

			template <class T> static T *copy_field(char *&to, unsigned to_capacity, const T *from, unsigned from_capacity)
			{
				unsigned bytes_to_copy = sizeof(T) * from_capacity;
				memcpy(to, from, bytes_to_copy);
				auto ret = (T *)to;
				to += sizeof(T) * to_capacity;
				return ret;
			}

			// Reclaims the memory used by the specified instance. This will move
			// the last instance into the reclaimed spot, which means its instance
			// reference will be invalidated.
			void reclaim(Instance i);

			// Allocates memory for the specified number of instances.
			void allocate(unsigned sz);

			// Blob for storing instance data.
			struct Blob
			{
				Blob() : size(), capacity(), buffer() {}
				unsigned size;		// Number of instances stored.
				unsigned capacity;	// Number of instances we have room for.
				void *buffer;
			};

			struct entity_hash
			{
				unsigned operator()(EntityRef t) const { return t; }
			};

			typedef HashMap<EntityRef, unsigned, entity_hash> EntityMap;

			Allocator &_allocator;
			EntityManagerApi* _entity_manager;
			EntityMap _map;					// Maps from entity to component instance
			Blob _blob;						// Blob holding all component data
			EntityRef *_entity;				// Entity array (points into blob)

			static const int COMPONENT_MARKER = 0x21a4cb82;
			static GCEntityComponent& cast(ComponentPtr component);

			/////// This is the interface that subclasses implement to provide either single instance of multi instance implementations

				// Allocates memory for the specified number of instances.
				virtual unsigned allocate_size(unsigned sz) = 0;

				// Change all reference to `to` to instead refer to `from`, this is used
				// when an instance is moved.
				virtual void change_references(Instance to, Instance from) = 0;

				// Moves the data for the instance `from` to the instance `to`.
				virtual void move_data(Instance to, Instance from) = 0;

				// Copies all data fields from `from` into our data structure. You should
				// override this to copy component specific data.
				virtual void copy_fields(char *to, unsigned to_capacity, unsigned from_capacity) = 0;

			Random random;
	};

	// A base implementation that allows one Instance per Entity
	// You need to implement the IGCEntityComponent interface in your subclass
	class SingleInstanceEntityComponent : public GCEntityComponent
	{
		public:
			SingleInstanceEntityComponent(Allocator &allocator, EntityManagerApi* entity_manager);

		private:
			InstanceId *_id;				// Id array (points into blob)

		protected:
			//////// EntityComponent C API
			Instance create(EntityRef entity, InstanceId instance_id) override;
			void destroy(Instance i) override;
			void destroy_all(EntityRef entity) override;
			Instance lookup_instance(EntityRef entity, InstanceId id) const override;
			EntityInstanceId lookup_instance_id(Instance instance) const override;
			void spawn(const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data) override;
			void set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices) override;
			void spawned(const EntityRef *entities, unsigned num_entities) override;
			Instance first_instance(EntityRef entity) const override;
			Instance next_instance(InstanceId instance) const override;

			unsigned allocate_size(unsigned sz) override;
			void change_references(Instance to, Instance from) override;
			void move_data(Instance to, Instance from) override;
			void copy_fields(char *to, unsigned to_capacity, unsigned from_capacity) override;
	};

	// A base implementation that allows multiple Instances per Entity
	// You need to implement the IGCEntityComponent interface in your subclass
	class MultiInstanceEntityComponent : public GCEntityComponent
	{
		public:
			MultiInstanceEntityComponent(Allocator &allocator, EntityManagerApi* entity_manager);

		private:
			InstanceId *_id;				// Id array (points into blob)
			Instance *_next_component;		// Next component for entity (points into blob).

			// Returns the previous instance to the specified one.
			Instance prev_component(Instance i) const;
		protected:
			//////// EntityComponent C API
			Instance create(EntityRef entity, InstanceId instance_id) override;
			void destroy(Instance i) override;
			void destroy_all(EntityRef entity) override;
			Instance lookup_instance(EntityRef entity, InstanceId id) const override;
			EntityInstanceId lookup_instance_id(Instance instance) const override;
			void spawn(const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data) override;
			void set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices) override;
			void spawned(const EntityRef *entities, unsigned num_entities) override;
			Instance first_instance(EntityRef entity) const override;
			Instance next_instance(InstanceId instance) const override;

			unsigned allocate_size(unsigned sz) override;
			void change_references(Instance to, Instance from) override;
			void move_data(Instance to, Instance from) override;
			void copy_fields(char *to, unsigned to_capacity, unsigned from_capacity) override;
	};

	// This is a template that can manage EntityComponent instances
	//
	// It registers the API and have helpers for creating a global component as well
	// as creating and registering components tied to a specific owner.
	//
	// Your COMPONENT class should override the static setup_api if it wants to handle
	// a extension API or a property API. The default methods for callbacks and lookups
	// are provided by this class, make a subclass implementing the construction/destruction
	// of instances via the allocate_component and dispose_component virtual functions.
	template <typename COMPONENT> class ComponentManager
	{
	public:
		ComponentManager(Allocator &allocator, ScriptApi *c_api, uint32_t &component_type_id32);
		virtual ~ComponentManager();

		COMPONENT *create_component(void *optional_owner);
		void destroy_component(void *optional_owner);
		COMPONENT *get_component(void *optional_owner) const;

	protected:
		// Your destructor must call dispose_all_components to deallocate any
		// still alive components
		void dispose_all_components();

		// Create an instance of your Component
		virtual COMPONENT *allocate_component(Allocator &allocator, void *optional_owner) = 0;
		// Dispose an instance of your Component
		virtual void dispose_component(Allocator &allocator, COMPONENT *component, void *optional_owner) = 0;

		const ScriptApi *c_api;
	private:
		Allocator &allocator;
		static uint32_t component_type_id32;
		static HashMap<void *, COMPONENT*> *component_map;
		ComponentApi base_component_api;
	};

	template <typename COMPONENT> HashMap<void *, COMPONENT*> * ComponentManager<COMPONENT>::component_map = nullptr;
	template <typename COMPONENT> uint32_t ComponentManager<COMPONENT>::component_type_id32;
}

#include "entity_component.inl"
