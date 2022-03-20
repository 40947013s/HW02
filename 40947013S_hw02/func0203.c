#include "hw0203.h"
    
Entity *Entity_ctor(Entity *this)
{
    this->hp = 100;
    this->is_dead = Entity_is_dead;
    return this;
}

void Entity_dtor(Entity *this)
{
    this->hp = 0;
    free(this);
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
    this->is_dead = Entity_is_dead;
    this->is_despair = Shoujo_is_despair;
    this->do_wish = Shoujo_do_wish;
    this->despair = Shoujo_despair;
    return this;
}

void Shoujo_dtor(Shoujo *this)
{
    this->base.hp = 0;
    this->name = 0;
    this->wish = 0;
    this->kimoji = 0;
    free(this);
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
    this->is_dead = Entity_is_dead;
    this->do_wish = Mahoushoujo_do_wish;
    this->attack = Mahoushoujo_attack;
    this->skill = skill;
}

void Mahoushoujo_dtor(Mahoushoujo *this)
{
    this->base.base.hp = 0;
    this->base.name = 0;
    this->base.wish = 0;
    this->base.kimoji = 0;
    this->atk = 0;
    free(this);
}

void Mahoushoujo_do_wish(void *this)
{
    Mahoushoujo *ans = this;
    puts(ans->base.wish);
    puts("But nothing is good\n");
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
    puts("Watashii de, hondo baga\n");
    return;    
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish)
{
    Shoujo_ctor(&this->base, name, wish);
    this->atk = 30;
    this->is_dead = Entity_is_dead;
    this->base.base.hp *= 50;
    this->attack = Majo_attack;
    this->kekkai = Majo_kekkai;
}

void Majo_dtor(Majo *this)
{
    this->base.base.hp = 0;
    this->base.name = 0;
    this->base.wish = 0;
    this->base.kimoji = 0;
    this->atk = 0;
    this->atk = 0;
    free(this);
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
    Majo *mj;
    mj->base = mhsj->base;
    mj->atk = mhsj->atk;   
    return mj;
}

void Madoka_skill(void *this, void *target)
{
    puts("Madoka become god, end.\n");
    return;
}

void Homura_skill(void *this, void *target)
{
    Shoujo *Homura = this;
    if(Homura->base.hp < 50)
        puts("This round is hopeless, Homura go to next round.\n");
    return;
}

void Sayaka_skill(void *this, void *target)
{
    Shoujo *Sayaka = this;
    Sayaka->base.hp += 30;
    Sayaka->kimoji-= 30;
    return;
}

void Kyoko_skill(void *this, void *target)
{
    Shoujo *Kyoko = this;
    Shoujo *tar = target;
    if(tar->name == "Sayaka")
    {
        Kyoko->base.hp = 0;
        tar->base.hp = 0;
    }
}
