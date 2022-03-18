#include "hw0203.h"

Entity *Entity_ctor(Entity *this)
{
    this->hp = 100;
    this->is_dead = Entity_is_dead(this);
    return this;
}

void Entity_dtor(Entity *this)
{
    this->hp = 0;
    this->is_dead = Entity_is_dead(this);
    free(this);
    return;
}

int Entity_is_dead(void *this)
{
    return this->hp == 0 ? 1 : 0;
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish)
{
    Entity *entity;
    this->base = Entity_ctor(entity);
    this->name = (char*)name;
    this->wish = (char*)wish;
    this->kimoji = 100;
    this->is_dead = 0;
    this->is_despair = 0;
    return this;
}

void Shoujo_dtor(Shoujo *this)
{
    Entity_dtor(&this->base);
    this->name = 0;
    this->wish = 0;
    this->kimoji = 0;
    this->despair = 0;
    this->is_dead = 0;
    free(this);
}

int Shoujo_is_despair(void *this)
{
    return this->kimoji <= 100 ? 1 : 0;
}

void Shoujo_despair(void *this)
{
    this->base.hp = 0;
    return;
}

void Shoujo_do_wish(void *this)
{
    printf("%s\n", this->wish);
    return;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill)
{
    Shoujo *mhsj;
    this->base = Shoujo_ctor(mhsj, name, wish);
    this->base.base.hp *= 3;
    this->atk = 100;
}

void Mahoushoujo_dtor(Mahoushoujo *this)
{
    Shoujo_dtor(&this->base);
    this->atk = 0;
    free(this);
}

void Mahoushoujo_do_wish(void *this)
{
    Shoujo_do_wish(&this->base);
    printf("But nothing is good\n");
    this->base.kimoji -= 10;
    return;
}

void Mahoushoujo_attack(Mahoushoujo *this, void *enemy)
{
    
}

void Shoujo_despair(void *this)
{
    printf("Watashii de, hondo baga\n");
    mhsj_to_mj(this); //turn itself to Mojo????
    return;    
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish)
{
    Shoujo *mj;
    this->base = Shoujo_ctor(mj, name, wish);
    this->base.base.hp *= 50;
    this->atk = 30;
}

void Majo_dtor(Majo *this)
{
    Shoujo_dtor(&this->base);
    this->atk = 0;
    free(this);
}

void Majo_attack(Majo *this, void *enemy)
{
    
}

void Majo_kekkai(Majo *this, Shoujo *sj)
{
    sj->kimoji -= 100;
    return;
}

void Majo_despair(void *this)
{
    return;
}

Majo *mhsj_to_mj(Mahoushoujo *mhsj)
{
    Majo *mj;
    *mj->base = *mhsj->base;
    mj->atk = mhsj->atk;    
}

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
        is_dead
}
