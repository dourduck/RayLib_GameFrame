#ifndef FSM_H
#define FSM_H
#include "base.h"

typedef enum {
  FSM_KIND_SLIME,
  FSM_KIND_GOBLIN,
  FSM_KIND_DRAGON,
} FSM_Kind;

typedef enum {
  FSM_STATE_SLIME_IDLE,
  FSM_STATE_SLIME_SCAVENGING,
  FSM_STATE_SLIME_FLEEING,
  FSM_STATE_SLIME_DEAD,
  FSM_STATE_SLIME_COUNT,
} FSM_State_Slime;

typedef enum {
  FSM_EVENT_SLIME_ATE,
  FSM_EVENT_SLIME_HUNGER,
  FSM_EVENT_SLIME_DEATH,
  FSM_EVENT_SLIME_COUNT,
} FSM_Event_Slime;
typedef struct {
  FSM_State_Slime current_state;
} FSM_Slime;

typedef enum {
  FSM_STATE_GOBLIN_IDLE,
  FSM_STATE_GOBLIN_CHASE,
  FSM_STATE_GOBLIN_FLEE,
  FSM_STATE_GOBLIN_COUNT,
} FSM_State_Goblin;
typedef enum {
  FSM_EVENT_GOBLIN_CALL,
  FSM_EVENT_GOBLIN_COUNT,
} FSM_Event_Goblin;
typedef struct {
  FSM_State_Goblin current_state;
} FSM_Goblin;

typedef enum {
  FSM_STATE_DRAGON_COUNT,
} FSM_State_Dragon;
typedef enum {
  FSM_EVENT_DRAGON_ROAR,
  FSM_EVENT_DRAGON_COUNT,
} FSM_Event_Dragon;
typedef struct {
  FSM_State_Dragon current_state;
} FSM_Dragon;

typedef struct {
  FSM_Kind kind;

  union {
    FSM_Slime slime;
    FSM_Goblin goblin;
    FSM_Dragon dragon;
  };
} FSM;

typedef struct {
  FSM_Kind kind;

  i32 entity_id;

  union {
    FSM_Event_Slime slime_event;
    FSM_Event_Goblin goblin_event;
    FSM_Event_Dragon dragon_event;
  };
} FSM_Command;

typedef struct {
  FSM_Command *commands;
  i32 count;
} FSM_Queue;

#endif

/* vim:set ts=3 sw=2 sts=2 et: */
