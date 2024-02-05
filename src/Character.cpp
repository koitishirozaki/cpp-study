#include "Character.h"
#include "raymath.h"

Character::Character(int windowWidth, int windowHeight, float worldScale) : scale(worldScale)
{
    // static_cast casts a variable to a different type and checks if the conversion iscompatible
    screenPos = {static_cast<float>(windowWidth) / 2.f - scale * (0.5f * width),
                 static_cast<float>(windowHeight) / 2.f - scale * (0.5f * height)};

    width = spritesheet.width / maxFrames;
    height = spritesheet.height;
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    // Updating world pos, facing direction and animation
    if (Vector2Length(direction) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? facingDirection = -1.f : facingDirection = 1.f;
        spritesheet = runAnim;
    }
    else
    {
        spritesheet = idleAnim;
    }

    // Cycling frames
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
        {
            frame = 0;
        }
    }

    Rectangle source{frame * width, 0.f, facingDirection * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(spritesheet, source, dest, Vector2{}, 0.f, WHITE);
}

Rectangle Character::getCollisionRect()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}