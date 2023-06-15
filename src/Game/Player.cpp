#include "Player.hpp"

void Player::Fire()
{
    Projetile *p = new Projetile(this, player, rect.x + rect.w / 2, rect.y + rect.h / 2, angle, renderer);
    projetiles.push_back(p);
    objects->push_back(p);
}