#include "raylib.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    int windowWidth{800};
    int windowHeight{480};

    InitWindow(windowWidth, windowHeight, "Abacate");
    SetTargetFPS(60);

    // Load World
    Texture2D world = LoadTexture("resources/nature_tileset/OpenWorldMap24x24.png");
    Vector2 worldPos{0.0, 0.0};
    float mapScale{4.f};

    // Load player
    Character knight = Character(windowWidth, windowHeight, mapScale);

    // Load Prop
    Prop props[2]{
        Prop(Vector2{0.f, 0.f}, LoadTexture("resources/nature_tileset/Rock.png"), mapScale),
        Prop(Vector2{400, 500}, LoadTexture("resources/nature_tileset/Log.png"), mapScale),
    };

    Enemy goblin{
        Vector2{},
        LoadTexture("resources/characters/goblin_idle_spritesheet.png"),
        LoadTexture("resources/characters/goblin_run_spritesheet.png"),
        mapScale};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw Map
        worldPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(world, worldPos, 0.0, mapScale, WHITE);

        // Draw Props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        // Goblin Tick
        goblin.tick(GetFrameTime());

        // Knight logic
        knight.tick(GetFrameTime());
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > world.width * mapScale ||
            knight.getWorldPos().y + windowHeight > world.height * mapScale)
        {
            knight.undoMovement();
        }
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRect(knight.getWorldPos()), knight.getCollisionRect()))
            {
                knight.undoMovement();
            }
        }

        EndDrawing();
    }
    CloseWindow();
};
