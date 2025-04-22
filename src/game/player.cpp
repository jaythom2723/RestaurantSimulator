#include "player.h"

#include <SDL2/SDL.h>

Player::Player(Renderer& r) : Entity(100, 100, 32, 32)
{
    texture = new Texture(r, "res/test.bmp");
}

Player::~Player()
{
    delete texture;
}

void Player::update(float deltaTime)
{
    tform.y += 75 * deltaTime;
}

void Player::draw(Renderer& r)
{
    SDL_Rect dst = { 0 };
    dst.x = tform.x;
    dst.y = tform.y;
    dst.w = tform.w;
    dst.h = tform.h;

    r.texCopy(texture->getTexture(), nullptr, &dst);
}

Texture *Player::getTexture()
{
    return texture;
}
