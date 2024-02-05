#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex, float worldScale);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRect(Vector2 knightPos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{};
};