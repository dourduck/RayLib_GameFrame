#ifndef EVENT_H
#define EVENT_H

/* vvv [ CONTEXT DEPENDANT ] vvv */

typedef struct {
  int key;
} EventKeyPressed;

typedef union {
  EventKeyPressed key_pressed;
} EventData;

typedef enum {
  EVENT_KEY_PRESSED,
  EVENT_COUNT,
} EventKind;

typedef struct {
  EventKind kind;
  EventData data;
} Event;

typedef void (*EventHandle)(Event *e);

/* vvv [ EVENT HANDLES ] vvv */

void Event_Handle_KeyPressed_impl(EventKeyPressed e);
void Event_Handle_KeyPressed(Event *e);

/* ^^^ [ EVENT HANDLES ] ^^^ */
/* vvv [ EVENT TABLE ] vvv */

/* Building table from handles, order matters, it should correspond with
 * EventKind(s)
 */
static const EventHandle event_table[EVENT_COUNT] = {
    Event_Handle_KeyPressed,
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
