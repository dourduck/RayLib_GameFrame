#include "event.h"
#include "entity.h"
#include "raylib.h"
#include "raymath.h"
// #include <stdio.h>

/* vvv [ CONTEXT DEPENDANT ] vvv */

/* vvv [ EVENT HANDLES ] vvv */
// void Event_Handle_PlaceHolder_Impl(EventPlaceHolder e) {
//   printf("(X: %d, Y: %d)", e.x, e.y);
// }
// void Event_Handle_PlaceHolder(Event *e) {
//   Event_Handle_PlaceHolder_Impl(e->data.place_holder);
// }

void Event_Handle_Input_Impl(EventInput e) {
  for (i32 i = 0; i < e.world->count; i++) {
    Entity _entity = e.world->entities[i];
    i32 _trait_mask = archetype_table[ARCHETYPE_PLAYER];

    if ((_entity.traits & _trait_mask) == _trait_mask) {
      f32 speed = _entity.speed * e.delta_time;

      Vector2 vel = Vector2Zero();

      if (e.key_down_north) {
        vel.y -= 1.0f;
        // printf("North Key Pressed!\n");
      }
      if (e.key_down_east) {
        vel.x += 1.0f;
        // printf("East Key Pressed!\n");
      }
      if (e.key_down_south) {
        vel.y += 1.0f;
        // printf("South Key Pressed!\n");
      }
      if (e.key_down_west) {
        vel.x -= 1.0f;
        // printf("West Key Pressed!\n");
      }
      vel = Vector2Normalize(vel);

      vel.x *= speed;
      vel.y *= speed;

      e.world->entities[i].velocity.x = vel.x;
      e.world->entities[i].velocity.y = vel.y;
    }
  }
}

void Event_Handle_Input(Event *e) {
  Event_Handle_Input_Impl(e->data.event_input);
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
