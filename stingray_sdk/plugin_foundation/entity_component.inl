
namespace stingray_plugin_foundation {

	///////////////////// EntityComponent

	inline EntityComponent::EntityComponent()
		: _marker(COMPONENT_MARKER)
	{ }

	inline EntityComponent::~EntityComponent()
	{ }

	inline EntityComponent& EntityComponent::cast(ComponentPtr component)
	{
		XENSURE(component != nullptr);
		auto impl = (EntityComponent*)component;
		XENSURE(impl->marker_valid());
		return *impl;
	}

	inline void EntityComponent::setup_api(ComponentApi &api)
	{
		api.create = [](ComponentPtr component, EntityRef entity, InstanceId instance_id) -> Instance
			{
				return cast(component).create(entity, instance_id);
			};
		api.destroy = [](ComponentPtr component, Instance i)
			{
				cast(component).destroy(i);
			};
		api.destroy_all = [](ComponentPtr component, EntityRef entity)
			{
				cast(component).destroy_all(entity);
			};
		api.lookup_instance = [](ComponentPtr component, EntityRef entity, InstanceId id) -> Instance
			{
				return cast(component).lookup_instance(entity, id);
			};
		api.lookup_instance_id = [](ComponentPtr component, Instance i) -> EntityInstanceId
			{
				return cast(component).lookup_instance_id(i);
			};
		api.spawn = [](ComponentPtr component, const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data)
			{
				cast(component).spawn(entities, num_instances, entity_indicies, instance_ids, data);
			};
		api.set_parent = [](ComponentPtr component, const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices)
			{
				cast(component).set_parent(entities, num_entities, parent_indices);
			};
		api.spawned = [](ComponentPtr component, const EntityRef *entities, unsigned num_entities)
			{
				cast(component).spawned(entities, num_entities);
			};
		api.first_instance = [](ComponentPtr component, EntityRef entity) -> Instance
			{
				return cast(component).first_instance(entity);
			};
		api.next_instance = [](ComponentPtr component, Instance i) -> Instance
			{
				return cast(component).next_instance(i);
			};
	}



	///////////////////// GCEntityComponent

	inline GCEntityComponent::GCEntityComponent(Allocator& allocator, EntityManagerApi* entity_manager)
		: EntityComponent()
		, _allocator(allocator)
		, _entity_manager(entity_manager)
		, _map(_allocator)
		, _blob()
		, _entity()
	{

	}

	inline GCEntityComponent::~GCEntityComponent()
	{
		_allocator.deallocate(_blob.buffer);
	}

	inline void GCEntityComponent::garbage_collect_entities()
	{
		auto i = random(_blob.size);
		while (i && _entity[i] != nil_entity() && (_entity_manager->is_alive(_entity[i]) == 0) ) {
			destroy(i);
			i = (i + 1) % _blob.size;
		}
	}

	inline void GCEntityComponent::garbage_collect_instances()
	{
		auto i = random(_blob.size);
		while (i && _entity[i] == nil_entity()) {
			reclaim(i);
			i = (i + 1) % _blob.size;
		}
	}

	inline void GCEntityComponent::reclaim(Instance i)
	{
		const Instance last = _blob.size - 1;
		change_references(i, last);
		move_data(i, last);
		--_blob.size;
	}

	inline void GCEntityComponent::allocate(unsigned sz)
	{
		XENSURE(sz >= _blob.size);
		Blob old = _blob;
		auto fs = allocate_size(sz);
		_blob.buffer = _allocator.allocate(sz * fs);
		memset(_blob.buffer, 0, sz*fs);
		_blob.capacity = sz;
		copy_fields((char *)_blob.buffer, _blob.capacity, old.capacity);
		_allocator.deallocate(old.buffer);

		// Instance 0 is reserved for nil component.
		if (!_blob.size && _blob.capacity)
			_blob.size = 1;
	}




	///////////////////// SingleInstanceEntityComponent

	inline SingleInstanceEntityComponent::SingleInstanceEntityComponent(Allocator &allocator, EntityManagerApi* entity_manager)
		: GCEntityComponent(allocator, entity_manager)
		, _id()
	{ }

	inline Instance SingleInstanceEntityComponent::create(EntityRef entity, InstanceId instance_id)
	{
		auto current = _map.get(entity, 0);
		if (!is_nil_instance(current))
			return current;

		if (_blob.size >= _blob.capacity)
			allocate(_blob.capacity * 2);
		++_blob.size;

		const auto i = _blob.size - 1;
		_entity[i] = entity;
		_id[i] = instance_id;
		_map[entity] = i;

		create_instance(i);

		return i;
	}

	inline void SingleInstanceEntityComponent::destroy(Instance i)
	{
		destroy_instance(i);

		const EntityRef e = _entity[i];
		_map.erase(e);
		_entity[i] = nil_entity();
		_id[i] = nil_instance_id();
	}

	inline void SingleInstanceEntityComponent::destroy_all(EntityRef e)
	{
		destroy(lookup_instance(e, 0));
	}

	inline Instance SingleInstanceEntityComponent::lookup_instance(EntityRef e, InstanceId) const
	{
		return _map.get(e, 0);
	}

	inline EntityInstanceId SingleInstanceEntityComponent::lookup_instance_id(Instance instance) const
	{
		return{ _entity[instance], _id[instance] };
	}

	inline void SingleInstanceEntityComponent::spawn(const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data)
	{
		for (unsigned n = 0; n < num_instances; ++n) {
			unsigned entity_index = entity_indicies[n];
			unsigned instance_id = instance_ids[n];
			EntityRef entity = entities[entity_index];
			Instance i = create(entity, instance_id);
			spawn_instance(entity, i, instance_id, data);
		}
	}

	inline void SingleInstanceEntityComponent::set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices)
	{
		entity_set_parent(entities, num_entities, parent_indices);
	}

	inline void SingleInstanceEntityComponent::spawned(const EntityRef *entities, unsigned num_entities)
	{
		instances_spawned(entities, num_entities);
	}

	inline Instance SingleInstanceEntityComponent::first_instance(EntityRef entity) const
	{
		return _map.get(entity, 0);
	}

	inline Instance SingleInstanceEntityComponent::next_instance(InstanceId instance) const
	{
		return nil_instance();
	}

	inline unsigned SingleInstanceEntityComponent::allocate_size(unsigned sz)
	{
		return (unsigned)(sizeof(EntityRef) + sizeof(InstanceId) + instance_total_field_size());
	}

	inline void SingleInstanceEntityComponent::change_references(Instance to, Instance from)
	{
		change_instance_references(to, from);

		const EntityRef e = _entity[from];
		_map[e] = to;
	}

	inline void SingleInstanceEntityComponent::move_data(Instance to, Instance from)
	{
		_entity[to] = _entity[from];
		_id[to] = _id[from];

		_entity[from] = nil_entity();
		_id[from] = nil_instance_id();

		move_instance_data(to, from);
	}

	inline void SingleInstanceEntityComponent::copy_fields(char *to, unsigned to_capacity, unsigned from_capacity)
	{
		_entity = copy_field(to, to_capacity, _entity, from_capacity);
		_id = copy_field(to, to_capacity, _id, from_capacity);
		copy_component_fields(to, to_capacity, from_capacity);
	}


	inline MultiInstanceEntityComponent::MultiInstanceEntityComponent(Allocator &allocator, EntityManagerApi* entity_manager)
		: GCEntityComponent(allocator, entity_manager)
		, _id()
		, _next_component()
	{
	}




	///////////////////// MultiInstanceEntityComponent

	inline Instance MultiInstanceEntityComponent::prev_component(Instance i) const
	{
		const EntityRef e = _entity[i];
		Instance iter = _map.get(e, 0);
		while (is_some_instance(iter)) {
			const Instance iter_next = _next_component[iter];
			if (iter_next == i)
				return iter;
			iter = iter_next;
		}
		return nil_instance();
	}

	inline Instance MultiInstanceEntityComponent::create(EntityRef entity, InstanceId instance_id)
	{
		if (_blob.size >= _blob.capacity)
			allocate(_blob.capacity * 2);
		++_blob.size;

		const auto i = _blob.size - 1;

		_entity[i] = entity;
		_next_component[i] = _map.get(entity, 0);
		_id[i] = instance_id;
		_map[entity] = i;

		create_instance(i);

		return i;
	}

	inline void MultiInstanceEntityComponent::destroy(Instance i)
	{
		destroy_instance(i);

		const EntityRef e = _entity[i];
		const Instance prev = prev_component(i);
		const Instance next = _next_component[i];

		if (is_some_instance(prev))
			_next_component[prev] = next;
		else if (is_some_instance(next))
			_map[e] = next;
		else
			_map.erase(e);

		_entity[i] = nil_entity();
		_id[i] = nil_instance_id();
		_next_component[i] = nil_instance();
	}

	inline void MultiInstanceEntityComponent::destroy_all(EntityRef e)
	{
		Instance i = _map.get(e, 0);
		while (is_some_instance(i)) {
			destroy_instance(i);
			auto next = _next_component[i];

			_entity[i] = nil_entity();
			_id[i] = nil_instance_id();
			_next_component[i] = nil_instance();

			i = next;
		}
		_map.erase(e);
	}

	inline Instance MultiInstanceEntityComponent::lookup_instance(EntityRef e, InstanceId id) const
	{
		Instance iter = _map.get(e, 0);
		while (is_some_instance(iter)) {
			if (_id[iter] == id)
				return iter;
			iter = _next_component[iter];
		}
		return iter;
	}

	inline EntityInstanceId MultiInstanceEntityComponent::lookup_instance_id(Instance instance) const
	{
		return { _entity[instance], _id[instance] };
	}

	inline void MultiInstanceEntityComponent::spawn(const EntityRef *entities, unsigned num_instances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data)
	{
		for (unsigned n = 0; n < num_instances; ++n) {
			unsigned entity_index = entity_indicies[n];
			unsigned instance_id = instance_ids[n];
			EntityRef entity = entities[entity_index];
			Instance i = create(entity, instance_id);
			spawn_instance(entity, i, instance_id, data);
		}
	}

	inline void MultiInstanceEntityComponent::set_parent(const EntityRef *entities, unsigned num_entities, const unsigned *parent_indices)
	{
		entity_set_parent(entities, num_entities, parent_indices);
	}

	inline void MultiInstanceEntityComponent::spawned(const EntityRef *entities, unsigned num_entities)
	{
		instances_spawned(entities, num_entities);
	}

	inline Instance MultiInstanceEntityComponent::first_instance(EntityRef entity) const
	{
		return _map.get(entity, 0);
	}

	inline Instance MultiInstanceEntityComponent::next_instance(InstanceId instance) const
	{
		return _next_component[instance];
	}

	inline unsigned MultiInstanceEntityComponent::allocate_size(unsigned sz)
	{
		return (unsigned)(sizeof(EntityRef) + sizeof(InstanceId) + sizeof(InstanceId) + instance_total_field_size());
	}

	inline void MultiInstanceEntityComponent::change_references(Instance should_refer_to, Instance refering_to)
	{
		change_instance_references(should_refer_to, refering_to);

		const EntityRef e = _entity[refering_to];

		const Instance first = _map.get(e, 0);
		if (first == refering_to)
			_map[e] = should_refer_to;
		else
			_next_component[prev_component(refering_to)] = should_refer_to;
	}

	inline void MultiInstanceEntityComponent::move_data(Instance to, Instance from)
	{
		_entity[to] = _entity[from];
		_id[to] = _id[from];
		_next_component[to] = _next_component[from];

		_entity[from] = nil_entity();
		_id[from] = nil_instance_id();
		_next_component[from] = nil_instance();

		move_instance_data(to, from);
	}

	inline void MultiInstanceEntityComponent::copy_fields(char *to, unsigned to_capacity, unsigned from_capacity)
	{
		_entity = copy_field(to, to_capacity, _entity, from_capacity);
		_id = copy_field(to, to_capacity, _id, from_capacity);
		_next_component = copy_field(to, to_capacity, _next_component, from_capacity);
		copy_component_fields(to, to_capacity, from_capacity);
	}




	///////////////////// ComponentManager

	template <typename COMPONENT> ComponentManager<COMPONENT>::ComponentManager(Allocator &allocator, ScriptApi *c_api, uint32_t &component_type_id32)
		: allocator(allocator)
		, c_api(c_api)
		, base_component_api({ nullptr })
	{
		COMPONENT::setup_api(base_component_api);
		typedef HashMap<void *, COMPONENT*> ComponentMap;
		component_map = MAKE_NEW(allocator, ComponentMap, allocator);
		ComponentManager::component_type_id32 = component_type_id32;
		base_component_api.component = [](void *owner) -> ComponentPtr
		{
			if (component_map == nullptr)
				return nullptr;
			return (ComponentPtr)component_map->get(owner, nullptr);
		};
		base_component_api.type_name = []() {return ComponentManager::component_type_id32; };
		c_api->Entity->register_component_api(component_type_id32, &base_component_api);
	}

	template <typename COMPONENT> ComponentManager<COMPONENT>::~ComponentManager()
	{
		c_api->Entity->unregister_component_api(component_type_id32);
		MAKE_DELETE(allocator, component_map);
		component_map = nullptr;
		component_type_id32 = 0u;
	}

	template <typename COMPONENT> void ComponentManager<COMPONENT>::dispose_all_components()
	{
		for (auto & i = component_map->begin(); i != component_map->end(); ++i)
			dispose_component(allocator, i->second, i->first);
		component_map->clear();
	}

	template <typename COMPONENT> COMPONENT *ComponentManager<COMPONENT>::create_component(void *optional_owner)
	{
		COMPONENT* component = allocate_component(allocator, nullptr);
		component_map->insert(optional_owner, component);
		return component;
	}

	template <typename COMPONENT> void ComponentManager<COMPONENT>::destroy_component(void *optional_owner)
	{
		COMPONENT* component = component_map->get(optional_owner, nullptr);
		if (component != nullptr) {
			component_map->erase(optional_owner);
			dispose_component(allocator, component, optional_owner);
		}
	}

	template <typename COMPONENT> COMPONENT* ComponentManager<COMPONENT>::get_component(void *optional_owner) const
	{
		return component_map->get(optional_owner, nullptr);
	}
}
