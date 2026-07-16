#ifndef EVENT_H
#define EVENT_H
#include "raylib.h"

/* vvv [ CONTEXT DEPENDANT ] vvv */

typedef struct {
  bool key_pressed_north;
  bool key_pressed_east;
  bool key_pressed_south;
  bool key_pressed_west;

  bool key_down_north;
  bool key_down_east;
  bool key_down_south;
  bool key_down_west;

  // int key_pressed;
  // int key_down;
  // int mouse_pressed;
  // int mouse_down;
  
  Vector2 mouse_position;
  bool mouse_pressed_left;
  bool mouse_pressed_right;
  bool mouse_down_left;
  bool mouse_down_right;
} EventInput;

typedef union {
  EventInput event_input;
} EventData;

typedef enum {
  EVENT_INPUT,
  EVENT_COUNT,
} EventKind;

typedef struct {
  EventKind kind;
  EventData data;
} Event;

typedef void (*EventHandle)(Event *e);

/* vvv [ EVENT HANDLES ] vvv */

void Event_Handle_Input_Impl(EventInput e);
void Event_Handle_Input(Event *e);

/* ^^^ [ EVENT HANDLES ] ^^^ */
/* vvv [ EVENT TABLE ] vvv */

/* Building table from handles, order matters, it should correspond with
 * EventKind(s)
 */
static const EventHandle event_table[EVENT_COUNT] = {
    Event_Handle_Input,
};
/* ^^^ [ EVENT TABLE ] ^^^ */

#define EVENT_QUEUE_SIZE 256
/* ^^^ [ CONTEXT DEPENDANT ] ^^^ */

typedef struct {
  Event events[EVENT_QUEUE_SIZE];
  int head;
  int tail;
  int count;
} EventQueue;

int EventQueue_Push(EventQueue *q, Event e);
int EvebtQueue_Pop(EventQueue *q, Event *out);

void EventQueue_Dispatch(Event *e);
void EventQueue_Process(EventQueue *q);

#endif
/* vim:set ts=3 sw=2 sts=2 et: */
