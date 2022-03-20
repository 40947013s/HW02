#include "hw0203.h"
    
Entity *Entity_ctor(Entity *this)
{
    this->hp = 100;
    this->is_dead = &Entity_is_dead;
    return this;
}

void Entity_dtor(Entity *this)
{
    this->hp = 0;
    return;
}

int Entity_is_dead(void *this)
{
    Entity *ans = this;
    return ans->hp <= 0 ? 1 : 0; 
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish)
{    
    Entity_ctor(&this->base); 
    this->name = (char*)name;
    this->wish = (char*)wish;
    this->kimoji = 100;
    this->is_dead = &Entity_is_dead;
    this->is_despair = &Shoujo_is_despair;
    this->do_wish = Shoujo_do_wish;
    this->despair = Shoujo_despair;
    return this;
}

void Shoujo_dtor(Shoujo *this)
{
    Entity_dtor(&this->base);
    this->name = NULL;
    this->wish = NULL;
    this->kimoji = 0;
}

int Shoujo_is_despair(void *this)
{
    Shoujo *ans = this;
    return ans->kimoji <= -100 ? 1 : 0;
}

void Shoujo_do_wish(void *this)
{
    Shoujo *ans = this;
    puts(ans->wish);
    return;
}

void Shoujo_despair(void *this)
{
    Shoujo *ans = this;
    ans->base.hp = 0;
    ans = this;
    return;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill)
{
    Shoujo_ctor(&this->base, name, wish);
    this->base.despair = Mahoushoujo_despair;
    this->atk = 100;
    this->base.base.hp *= 3;
    this->is_dead = &Entity_is_dead;
    this->do_wish = Mahoushoujo_do_wish;
    this->attack = Mahoushoujo_attack;
    this->skill = skill;
}

void Mahoushoujo_dtor(Mahoushoujo *this)
{
    Shoujo_dtor(&this->base);
    this->atk = 0;
}

void Mahoushoujo_do_wish(void *this)
{
    Mahoushoujo *ans = this;
    puts(ans->base.wish);
    puts("But nothing is good");
    ans->base.kimoji -= 10;
    return;
}

void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy)
{
    enemy->hp -= this->atk;
    return;
}

void Mahoushoujo_despair(void *this)
{
    puts("Watashii de, hondo baga");
    return;    
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish)
{
    Shoujo_ctor(&this->base, name, wish);
    this->atk = 10;
    this->is_dead = &Entity_is_dead;
    this->base.base.hp *= 50;
    this->attack = Majo_attack;
    this->kekkai = Majo_kekkai;
}

void Majo_dtor(Majo *this)
{
    Shoujo_dtor(&this->base);
    this->atk = 0;
}

void Majo_attack(Majo *this, Entity *enemy)
{
    enemy->hp -= this->atk;
    return;
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
    char *name = mhsj->base.name;
    char *wish = mhsj->base.wish;
    Majo *mj = Majo_ctor(malloc(sizeof(Majo)), name, wish);
    mj->base.base.hp = mhsj->base.base.hp;
    mj->base.kimoji = mhsj->base.kimoji;
    mj->atk = mhsj->atk;  
    return mj;
}

void Madoka_skill(void *this, void *target)
{
    puts("Madoka become god, end.");
    return;
}

void Homura_skill(void *this, void *target)
{
    Mahoushoujo *Homura = this;
    if(Homura->base.base.hp < 50)
        puts("This round is hopeless, Homura go to next round.");
    return;
}

void Sayaka_skill(void *this, void *target)
{
    Mahoushoujo *Sayaka = this;
    Sayaka->base.base.hp += 30;
    Sayaka->base.kimoji-= 30;
    return;
}

void Kyoko_skill(void *this, void *target)
{
    Mahoushoujo *Kyoko = this;
    Mahoushoujo *tar = target;
    if(tar->skill == Sayaka_skill)
    {
        Kyoko->base.hp = 0;
        Kyoko->base.is_dead = &Entity_is_dead;
        tar->base.hp = 0;
        tar->base.is_dead = &Entity_is_dead;
    }
    return;
}
