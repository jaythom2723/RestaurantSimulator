#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "texture.h"
#include "renderer.h"
#include "entity.h"


// THIS IS A TEST ENTITY CLASS
// TODO: REMOVE ME WHEN PROTOTYPING IS COMPLETE
class Player : public Entity
{
protected:
    Texture *texture;

public:
    Player(Renderer& r);
    virtual ~Player();

    void update(float deltaTime);
    void draw(Renderer& r);

    Texture *getTexture();
};

#endif // PLAYER_H_INCLUDED
