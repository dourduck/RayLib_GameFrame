#include "raylib.h"
#include "game.h"
#include "entity.h"
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
  }

  EntitySystem es_render = EntitySystem_Render_Create(&world);

  while (!WindowShouldClose()) {
    float delta_time = GetFrameTime();

    // Poll_Input();
    // Poll_Game(&game, delta_time);

    BeginDrawing();
    ClearBackground(GRAY);

    Update_Render(&es_render);

    EndDrawing();
  }

  CloseWindow();
}

/* vim:set ts=3 sw=2 sts=2 et: */
