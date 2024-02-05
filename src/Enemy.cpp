#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D tex, Texture2D run_tex, float scale) : worldPos(pos), spritesheet(tex),
                                                                           runAnim(run_tex), idleAnim(tex), scale(scale)
{
    width = spritesheet.width / maxFrames;
    height = spritesheet.height;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

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

void Enemy::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRect()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}