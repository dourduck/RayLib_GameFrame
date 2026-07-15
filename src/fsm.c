#include "fsm.h"
#include "entity.h"

static const FSM_State_Slime slime_states[FSM_EVENT_SLIME_COUNT]
                                         [FSM_STATE_SLIME_COUNT] = {
                                             {
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                             },
                                             {
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                             },
                                             {
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                                 FSM_STATE_SLIME_IDLE,
                                             }};

static const FSM_State_Slime goblin_states[FSM_EVENT_GOBLIN_COUNT]
                                          [FSM_STATE_GOBLIN_COUNT] = {};
static const FSM_State_Slime dragon_states[FSM_EVENT_DRAGON_COUNT]
                                          [FSM_STATE_DRAGON_COUNT] = {};

void FSM_Queue_PushCommand(FSM_Queue *q, FSM_Command c) {
  q->commands[q->count++] = c;
}

void FSM_Slime_Tick(FSM_Queue *slime_command_queue, Entity *e) {
  if (e->hunger > 30) {
    FSM_Command cmd = {.entity_id = e->id,
                       .slime_event = FSM_EVENT_SLIME_HUNGER};
    FSM_Queue_PushCommand(slime_command_queue, cmd);
  }
}

void FSM_Command_Slime_Process(World *world, i32 entity_id,
                               FSM_Event_Slime event) {
  FSM_State_Slime current =
      world->entities[entity_id].state_machine.slime.current_state;
  FSM_State_Slime next_state = slime_states[event][current];
  world->entities[entity_id].state_machine.slime.current_state = next_state;

  // if (event == FSM_EVENT_SLIME_ATE) {
  //   play sound or something
  // }
}

void FSM_Command_Goblin_Process(World *world, i32 entity_id,
                                FSM_Event_Goblin event) {
  FSM_State_Goblin current =
      world->entities[entity_id].state_machine.goblin.current_state;
  FSM_State_Goblin next_state = goblin_states[event][current];
  world->entities[entity_id].state_machine.goblin.current_state = next_state;

  // if (event == FSM_EVENT_GOBLIN_CALL) {
  //   // play sound or something
  // }
}
void FSM_Command_Dragon_Process(World *world, i32 entity_id,
                                FSM_Event_Dragon event) {
  FSM_State_Dragon current =
      world->entities[entity_id].state_machine.dragon.current_state;
  FSM_State_Dragon next_state = dragon_states[event][current];
  world->entities[entity_id].state_machine.dragon.current_state = next_state;

  // if (event == FSM_EVENT_DRAGON_ROAR) {
  //   // play sound or something
  // }
}

void FSM_Queue_Process(World *world, FSM_Queue *q) {
  for (i32 i = 0; i < q->count; i++) {
    FSM_Command cmd = q->commands[i];
    switch (cmd.kind) {
    case FSM_KIND_SLIME:
      FSM_Command_Slime_Process(world, cmd.entity_id, cmd.slime_event);
      break;
    case FSM_KIND_GOBLIN:
      FSM_Command_Goblin_Process(world, cmd.entity_id, cmd.goblin_event);
      break;
    case FSM_KIND_DRAGON:
      FSM_Command_Dragon_Process(world, cmd.entity_id, cmd.dragon_event);
      break;
    }
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
