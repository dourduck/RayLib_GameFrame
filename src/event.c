#include <stdio.h>


/* vvv [ CONTEXT DEPENDANT ] vvv */
typedef enum {
  EVENT_PLACEHOLDER,
  EVENT_COUNT,
} EventKind;

typedef struct {
  int x, y;
} EventPlaceHolder;

typedef union {
  EventPlaceHolder place_holder
} EventData;
/* ^^^ [ CONTEXT DEPENDANT ] ^^^ */

typedef struct {
  EventKind kind;
  EventData data;
} Event;

typedef void (*EventHandle)(Event *e);

/* vvv [ CONTEXT DEPENDANT ] vvv */
/* vvv [ EVENT HANDLES ] vvv */

void Event_Handle_PlaceHolder_Impl(EventPlaceHolder e) {
  printf("(X: %d, Y: %d)", e.x, e.y);
}
void Event_Handle_PlaceHolder(Event *e) {
  Event_Handle_PlaceHolder_Impl(e->data.place_holder);
}

/* ^^^ [ EVENT HANDLES ] ^^^ */
/* vvv [ EVENT TABLE ] vvv */

/* Building table from handles, order matters, it should correspond with
 * EventKind(s) */
static const EventHandle event_table[EVENT_COUNT] = {
    Event_Handle_PlaceHolder,
};

/* ^^^ [ CONTEXT DEPENDANT ] ^^^ */
/* ^^^ [ EVENT TABLE ] ^^^ */

/* vvv [ CONTEXT DEPENDANT ] vvv */
#define EVENT_QUEUE_SIZE 256
/* ^^^ [ CONTEXT DEPENDANT ] ^^^ */

typedef struct {
  Event events[EVENT_QUEUE_SIZE];
  int head;
  int tail;
  int count;
} EventQueue;

int Queue_Push(EventQueue *q, Event e) {
  if (q->count == EVENT_QUEUE_SIZE) {
    return 0;
  }
  q->events[q->tail] = e;
  q->tail = (q->tail + 1) % EVENT_QUEUE_SIZE;
  q->count++;
  return 1;
}
int Queue_Pop(EventQueue *q, Event *out) {
  if (q->count == 0) {
    return 0;
  }
  *out = q->events[q->head];
  q->head = (q->head + 1) % EVENT_QUEUE_SIZE;
  q->count--;
  return 1;
}

void Dispatch(Event *e) { event_table[e->kind](e); }

void Event_Queue_Process(EventQueue *q) {
  Event e;

  while (Queue_Pop(q, &e)) {
    Dispatch(&e);
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
