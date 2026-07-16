#include "entity.h"
#include "event.h"
#include "game.h"
#include "input.h"
#include "physics.h"
#include "raylib.h"
#include "render.h"

int main(void) {
  Environment environment = Environment_CreateDefault();
  Environment_InitWindow(&environment);

  World world;
  World_Init(&world);

  for (i32 i = 0; i < 10; i++) {
    i32 id = World_Entity_Create(&world, archetype_table[ARCHETYPE_SLIME]);
    float x = GetRandomValue(100, 400);
    float y = GetRandomValue(100, 400);
    world.entities[id].position = (Vector2){x, y};
    world.entities[id].color = GREEN;
  }

  EventQueue event_queue = {0};

  i32 player_id = World_Entity_Create(&world, archetype_table[ARCHETYPE_PLAYER]);
  world.entities[player_id].position = (Vector2){500, 500};
  world.entities[player_id].speed = 100.0f;
  world.entities[player_id].color = SKYBLUE;

  EntitySystem es_render = EntitySystemCreate_Render(&world);
  EntitySystem es_physics = EntitySystemCreate_Physics(&world);

  while (!WindowShouldClose()) {
    float delta_time = GetFrameTime();

    Pull_Input(&world, &event_queue, delta_time);

    EventQueue_Process(&event_queue);

    EntitySystemUpdate_Physics(&world, &es_physics);

    BeginDrawing();
    ClearBackground(GRAY);

    EntitySystemUpdate_Render(&world, &es_render);

    EndDrawing();
  }

  CloseWindow();
}

/* vim:set ts=3 sw=2 sts=2 et: */
