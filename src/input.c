#include "input.h"
#include "event.h"
#include "raylib.h"

void Pull_Input(World *world, EventQueue *q, f32 delta_time) {
  KeyboardKey north, east, south, west;

  north = KEY_W;
  west = KEY_A;
  south = KEY_S;
  east = KEY_D;

  bool mouse_pressed_left = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
  bool mouse_pressed_right = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
  bool mouse_down_left = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
  bool mouse_down_right = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
  Vector2 mouse_pos = GetMousePosition();

  EventInput event_input = {
      .world = world,
      .delta_time = delta_time,
      .key_pressed_north = IsKeyPressed(north),
      .key_pressed_east = IsKeyPressed(east),
      .key_pressed_south = IsKeyPressed(south),
      .key_pressed_west = IsKeyPressed(west),

      .key_down_north = IsKeyDown(north),
      .key_down_east = IsKeyDown(east),
      .key_down_south = IsKeyDown(south),
      .key_down_west = IsKeyDown(west),

      .mouse_position = mouse_pos,
      .mouse_pressed_left = mouse_pressed_left,
      .mouse_pressed_right = mouse_pressed_right,
      .mouse_down_left = mouse_down_left,
      .mouse_down_right = mouse_down_right,

  };

  Event e = {.kind = EVENT_INPUT, .data.event_input = event_input};

  EventQueue_Push(q, e);
}

/* vim:set ts=3 sw=2 sts=2 et: */
