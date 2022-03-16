#include "madoka.h"

Entity *Entity_ctor(Entity *this)
{
    Entity *new_entity = malloc(1, sizeof(Entity));
    new_entity = this;
}
