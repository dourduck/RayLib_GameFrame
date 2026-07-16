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

void EntitySystemUpdate(World *world, EntitySystem *entitySystem) {
  i32 trait_mask = entitySystem->traits_filter;
  EntitySystemUpdate_Internal(world, trait_mask,
                               entitySystem->implementation);
}

void EntitySystemUpdate_Internal(World *world, i32 trait_mask,
                                  EntitySystemImpl impl) {
  for (i32 i = 0; i < world->count; i++) {
    Entity entity = world->entities[i];
    if ((entity.traits & trait_mask) == trait_mask) {
      impl(world, entity.id);
    }
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
