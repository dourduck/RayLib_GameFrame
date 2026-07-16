#include "physics.h"
#include "entity.h"
#include "raymath.h"

void EntitySystemImpl_Physics(World *world, i32 entity_id) {
  Vector2 pos = world->entities[entity_id].position;
  Vector2 vel = world->entities[entity_id].velocity;
  Vector2 new_pos = Vector2Add(pos, vel);
  world->entities[entity_id].position = new_pos;
}

EntitySystem EntitySystemCreate_Physics() {
  i32 _traits_filter = TRAIT_PHYSICAL;

  EntitySystem _es_physics = {.traits_filter = _traits_filter,
                              .implementation = EntitySystemImpl_Physics};

  return _es_physics;
}

void EntitySystemUpdate_Physics(World *world, EntitySystem *es_physics) {
  EntitySystemUpdate(world, es_physics);
}

/* vim:set ts=3 sw=2 sts=2 et: */
