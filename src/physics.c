#include "physics.h"
#include "raymath.h"

void EntitySystemImpl_Physics(World *_world, i32 _entity_id) {
  Vector2 pos = _world->entities[_entity_id].position;
  Vector2 vel = _world->entities[_entity_id].velocity;
  Vector2 new_pos = Vector2Add(pos, vel);
  _world->entities[_entity_id].position = new_pos;
}

EntitySystem EntitySystem_Physics_Create(World *_world) {
  i32 _traits_filter = TRAIT_PHYSICAL;

  EntitySystem _es_physics = {.world = _world,
                              .traits_filter = _traits_filter,
                              .implementation = EntitySystemImpl_Physics};

  return _es_physics;
}

void Update_Physics(EntitySystem *_es_physics) {
  EntitySystem_Invoke(_es_physics);
}

/* vim:set ts=3 sw=2 sts=2 et: */
