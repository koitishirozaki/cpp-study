#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D tex, Texture2D run_tex, float scale);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRect();

private:
    // Props
    int width{};
    int height{};

    // Position
    Vector2 worldPos{};
    Vector2 screenPos{};
    float speed{4};
    Vector2 worldPosLastFrame{};
    float scale{};

    // Animation
    float facingDirection{1.f};
    float runningTime;
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};

    // Texture
    Texture2D spritesheet{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Texture2D idleAnim{LoadTexture("resources/characters/knight_idle_spritesheet.png")};
    Texture2D runAnim{LoadTexture("resources/characters/knight_run_spritesheet.png")};
};