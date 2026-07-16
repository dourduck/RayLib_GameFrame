#include "entity.h"

void World_Init(World *_world) {
  _world->count = 0;
  _world->next_id = 0;
}

i32 World_Entity_Create(World *world, i32 traits) {
  i32 entity_id = world->next_id++;
  world->entities[entity_id].id = entity_id;
  world->entities[entity_id].traits = traits;
  world->count++;
  return entity_id;
}

void EntitySystem_Invoke(EntitySystem *_entitySystem) {
  World *_world = _entitySystem->world;
  i32 _trait_mask = _entitySystem->traits_filter;
  EntitySystem_Invoke_Internal(_world, _trait_mask,
                               _entitySystem->implementation);
}

void EntitySystem_Invoke_Internal(World *_world, i32 _trait_mask,
                                  EntitySystemImpl impl) {
  for (i32 i = 0; i < _world->count; i++) {
    Entity _entity = _world->entities[i];
    if ((_entity.traits & _trait_mask) == _trait_mask) {
      impl(_world, _entity.id);
    }
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
