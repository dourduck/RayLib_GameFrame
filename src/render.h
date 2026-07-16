#ifndef RENDER_H
#define RENDER_H
#include "entity.h"

EntitySystem EntitySystemCreate_Render(World* world);
void EntitySystemUpdate_Render(World *world, EntitySystem *es_render);

#endif
