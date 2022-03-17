#include "hw0203.h"

void Madoka_skill(void *this, void *target)
{
    printf("Madoka become god, end.\n");
    return;
}

void Homura_skill(void *this, void *target)
{
    if(this->base.base.hp < 50)
        printf("This round is hopeless, Homura go to
next round.\n");
    return;
}

void Sayaka_skill(void *this, void *target)
{
    this->base.base.hp += 30;
    this->base.kimoj -= 30;
    return;
}

void Kyoko_skill(void *this, void *target)
{
    if(target->base.name == "Sayaka")
        
}
