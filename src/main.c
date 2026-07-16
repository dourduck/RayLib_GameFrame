#include "entity.h"
#include "event.h"
#include "game.h"
#include "input.h"
#include "raylib.h"
#include "render.h"
#include "physics.h"


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

  EntitySystem es_render = EntitySystem_Render_Create(&world);
  EventQueue event_queue = {0};

  i32 player_id = World_Entity_Create(&world, archetype_table[ARCHETYPE_PLAYER]);
  world.entities[player_id].position = (Vector2){500, 500};
  world.entities[player_id].speed = 100.0f;
  world.entities[player_id].color = SKYBLUE;

  EntitySystem es_physics = EntitySystem_Physics_Create(&world);

  while (!WindowShouldClose()) {
    float delta_time = GetFrameTime();

    Pull_Input(&world, &event_queue, delta_time);

    EventQueue_Process(&event_queue);

    Update_Physics(&es_physics);

    BeginDrawing();
    ClearBackground(GRAY);

    Update_Render(&es_render);

    EndDrawing();
  }

  CloseWindow();
}

/* vim:set ts=3 sw=2 sts=2 et: */
