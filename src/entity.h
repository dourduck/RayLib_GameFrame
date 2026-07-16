#ifndef ENTITY_H
#define ENTITY_H
#include  "raylib.h"
#include "base.h"
#include "fsm.h"

typedef enum {
  TRAIT_PLAYER = (1 << 0),
  TRAIT_PHYSICAL = (1 << 1),
  TRAIT_RENDERABLE = (1 << 2),
  TRAIT_MOVABLE = (1 << 3),
  TRAIT_WET = (1 << 4),
  TRAIT_FLYING = (1 << 5),
} Trait;

typedef enum {
  ARCHETYPE_PLAYER,
  ARCHETYPE_SLIME,
  ARCHETYPE_GOBLIN,
  ARCHETYPE_DRAGON,
  ARCHETYPE_COUNT
} Archetype;

static const i32 archetype_table[ARCHETYPE_COUNT] = {
    /* Player */
    TRAIT_PLAYER | TRAIT_RENDERABLE | TRAIT_PHYSICAL,
    /* Slime */
    TRAIT_RENDERABLE | TRAIT_WET,
    /* Goblin */
    TRAIT_RENDERABLE,
    /* Dragon */
    TRAIT_RENDERABLE | TRAIT_FLYING,
};

/* Entities should be heap allocated */
/* Probably use an arena allocator */
#define WORLD_ENTITY_MAX 128

typedef struct {
  i32 traits;
  Vector2 position;
  Vector2 velocity;
  float speed;
  i32 texture_id;
  FSM state_machine;
  i32 health;
  i32 hunger;
  i32 id;
  Color color;
} Entity;

typedef struct {
  Entity entities[WORLD_ENTITY_MAX];
  i32 next_id;
  i32 count;
} World;

/* f : Entity -> void */
typedef void (*EntitySystemImpl)(World *_world, i32 _entity_id);

typedef struct {
  World *world;
  i32 traits_filter;
  EntitySystemImpl implementation;
} EntitySystem;

void World_Init(World *_world);
i32 World_Entity_Create(World *world, i32 traits);

void EntitySystem_Invoke(EntitySystem *_entitySystem);
void EntitySystem_Invoke_Internal(World *_world, i32 _traitMask,
                                  EntitySystemImpl impl);

#endif

/* vim:set ts=3 sw=2 sts=2 et: */
