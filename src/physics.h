#ifndef PHYSICS_H
#define PHYSICS_H
#include "base.h"
#include "entity.h"

void EntitySystemImpl_Physics(World *world, i32 entity_id);
EntitySystem EntitySystemCreate_Physics();
void EntitySystemUpdate_Physics(World *world, EntitySystem *es_physics);

#endif
