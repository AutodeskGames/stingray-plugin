#pragma once

#include "c_api_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Manages the lifetime of an entity. */
struct EntityManagerApi
{
	EntityRef (*create)(const void *owner);
	void (*destroy)(EntityRef entity);
	int (*is_alive)(EntityRef entity);
	EntityRef (*spawn)(WorldPtr world, uint64_t entity_name_id64, const char *optional_debug_entity_name, ConstMatrix4x4Ptr transform);
};

/* Opaque struct representing the component api extension. */
struct ComponentExtensionApi;

/* Component property api. */
typedef struct ComponentPropertyApi {

	/* Set component propery value. */
	void (*set_property)(ComponentPtr component, Instance i, EntityPropertyKey key, struct EntityPropertyValue value);

	/* Get component property value. */
	struct EntityPropertyValue (*get_property)(ComponentPtr component, Instance i, EntityPropertyKey key, struct AllocatorObject *temp_allocator);

} ComponentPropertyApi;

/* Component Api. */
typedef struct ComponentApi
{
	/* Gets type name of the entity component. */
	uint32_t (*type_name)();

	/* Gets the component manager for the specified world. */
	ComponentPtr (*component)(void *owner);

	/* Creates a new component instance. */
	Instance (*create)(ComponentPtr component, EntityRef entity, InstanceId instance_id);

	/* Destroy component instance. */
	void (*destroy)(ComponentPtr component, Instance i);

	/* Destroy all instances of the entity. */
	void (*destroy_all)(ComponentPtr component, EntityRef entity);

	/* Gets the component instance from the specified component id. */
	Instance (*lookup_instance)(ComponentPtr component, EntityRef entity, InstanceId id);

	/* Gets the component instance id from the specified component instance. */
	struct EntityInstanceId (*lookup_instance_id)(ComponentPtr component, Instance i);

	/* Spawn component. */
	void (*spawn)(ComponentPtr component, const EntityRef *entities, unsigned num_intances, const unsigned *entity_indicies, const unsigned *instance_ids, const char *data);

	/* Set entity parent. */
	void (*set_parent)(ComponentPtr component, const EntityRef *entities, unsigned num_entities, const unsigned *parent_index);

	/* Called when the entity as been fully constructed and spawned. */
	void (*spawned)(ComponentPtr component, const EntityRef *entities, unsigned num_entities);

	/* Gets the first component instance for the entity. */
	Instance (*first_instance)(ComponentPtr component, EntityRef entity);

	/* Gets the next component instance. */
	Instance (*next_instance)(ComponentPtr component, Instance i);

	/* Gets the component property api. */
	ComponentPropertyApi *(*get_property_api)();

	/*
		Retrieves a pointer to the component type specific API.
		To use this cast the ComponentExtensionApi pointer to to the relevant definition represented in it's header file.
	*/
	struct ComponentExtensionApi *(*get_extension_api)();

} ComponentApi;

typedef ComponentApi *ComponentApiPtr;

struct EntityCApi
{
	struct EntityManagerApi* Manager;

	/*
		Retrieves a pointer to the Component API registered with the specified name.
		To use the member functions of the specified Component API cast the ComponentApiPtr to the relevant definition represented in it's header file."
	*/
	ComponentApiPtr (*component_api)(uint32_t name_id32);

	/*	Registers a pointer to a component api with the specified name, the caller is responsible for keeping it allocated.	*/
	void (*register_component_api)(uint32_t name_id32, ComponentApiPtr component_api);

	/*	Returns true (1) if a component api with the specified name has already been registered.	*/
	int (*has_component_api)(uint32_t name_id32);

	/*	Unregisters a component struct with the specified name.	*/
	void (*unregister_component_api)(uint32_t name_id32);

	/* Registers the entity component to the specified world. */
	void (*register_entity_component)(WorldPtr world_pointer, ComponentPtr component, struct ComponentApi *component_api);

	/* Unregisters the entity component from the specified world. */
	void (*unregister_entity_component)(WorldPtr world_pointer, ComponentPtr component);
};

#ifdef __cplusplus
}
#endif
