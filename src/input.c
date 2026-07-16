#include "raylib.h"
#include "input.h"

void Pull_Input(EventQueue *q) {
  int key = GetKeyPressed();

  if (key) {
    EventKeyPressed event_key_pressed = {.key = key};
    Event e = {.kind = EVENT_KEY_PRESSED,
               .data.key_pressed = event_key_pressed};

    EventQueue_Push(q, e);
  }
}

/* vim:set ts=3 sw=2 sts=2 et: */
