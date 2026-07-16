#include "render.h"
#include "entity.h"

void EntitySystemImpl_Render(World *world, i32 entity_id) {
  Vector2 pos = world->entities[entity_id].position;
  DrawCircleV(pos, 16, world->entities[entity_id].color);
}

/* vim:set ts=3 sw=2 sts=2 et: */
