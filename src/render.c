#include "entity.h"
#include "render.h"

void EntitySystemImpl_Render(World *_world, i32 _entity_id) {
  Vector2 pos = _world->entities[_entity_id].position;
  DrawCircleV(pos, 8, GREEN);
}

EntitySystem EntitySystem_Render_Create(World* _world) {
  i32 _traits_filter = TRAIT_RENDERABLE;

  EntitySystem _es_render = {.world = _world,
                             .traits_filter = _traits_filter,
                             .implementation = EntitySystemImpl_Render};

  return _es_render;
}

void Update_Render(EntitySystem *_es_render){
  EntitySystem_Invoke(_es_render);
}

/* vim:set ts=3 sw=2 sts=2 et: */
