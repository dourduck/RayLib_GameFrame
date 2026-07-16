#include "render.h"
#include "entity.h"

void EntitySystemImpl_Render(World *world, i32 entity_id) {
  Vector2 pos = world->entities[entity_id].position;
  DrawCircleV(pos, 16, world->entities[entity_id].color);
}

EntitySystem EntitySystemCreate_Render(World *world) {
  i32 traits_filter = TRAIT_RENDERABLE;

  return (EntitySystem){.traits_filter = traits_filter,
                        .implementation = EntitySystemImpl_Render};
}

void EntitySystemUpdate_Render(World *world, EntitySystem *es_render) {
  EntitySystemUpdate(world, es_render);
}

/* vim:set ts=3 sw=2 sts=2 et: */
