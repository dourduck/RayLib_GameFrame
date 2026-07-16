#include "event.h"
#include <stdio.h>

/* vvv [ CONTEXT DEPENDANT ] vvv */

/* vvv [ EVENT HANDLES ] vvv */
// void Event_Handle_PlaceHolder_Impl(EventPlaceHolder e) {
//   printf("(X: %d, Y: %d)", e.x, e.y);
// }
// void Event_Handle_PlaceHolder(Event *e) {
//   Event_Handle_PlaceHolder_Impl(e->data.place_holder);
// }

void Event_Handle_KeyPressed_impl(EventKeyPressed e) {
  printf("key pressed %d\n", e.key);
}

void Event_Handle_KeyPressed(Event *e) {
  Event_Handle_KeyPressed_impl(e->data.key_pressed);
}

/* ^^^ [ EVENT HANDLES ] ^^^ */

/* ^^^ [ CONTEXT DEPENDANT ] ^^^ */

int EventQueue_Push(EventQueue *q, Event e) {
  if (q->count == EVENT_QUEUE_SIZE) {
    return 0;
  }
  q->events[q->tail] = e;
  q->tail = (q->tail + 1) % EVENT_QUEUE_SIZE;
  q->count++;
  return 1;
}

int EvebtQueue_Pop(EventQueue *q, Event *out) {
  if (q->count == 0) {
    return 0;
  }
  *out = q->events[q->head];
  q->head = (q->head + 1) % EVENT_QUEUE_SIZE;
  q->count--;
  return 1;
}

void EventQueue_Dispatch(Event *e) { event_table[e->kind](e); }

void EventQueue_Process(EventQueue *q) {
  Event e;

  while (EvebtQueue_Pop(q, &e)) {
    EventQueue_Dispatch(&e);
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
