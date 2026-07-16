#ifndef PHYSICS_H
#define PHYSICS_H
#include "base.h"
#include "entity.h"

void EntitySystemImpl_Physics(World *_world, i32 _entity_id);
EntitySystem EntitySystem_Physics_Create(World *_world);
void Update_Physics(EntitySystem *_es_physics);

#endif
