#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRect() { return weaponCollisionRect; }
    float getHealth() const { return health; }
    void takeDamage(float damage);

private:
    Texture2D weapon{LoadTexture("resources/characters/weapon_sword.png")};
    int windowWidth{};
    int windowHeight{};
    Rectangle weaponCollisionRect{};
    float health{100.f};
};

#endif