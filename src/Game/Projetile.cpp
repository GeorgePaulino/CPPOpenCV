#include "Projetile.hpp"

void Projetile::CollisionEvent(int type)
{
    auto it = std::find(player->projetiles.begin(), player->projetiles.end(), this);
    if (it != player->projetiles.end())
    {
        player->projetiles.erase(it);
    }
    destroy = true;
}