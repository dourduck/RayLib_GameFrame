#ifndef RENDER_H
#define RENDER_H
#include "entity.h"

EntitySystem EntitySystem_Render_Create(World* _world);
void Update_Render(EntitySystem *_es_render);

#endif
