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
    Entity_dtor(&this->base);
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
    printf("%s\n", ans->wish);
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
    Shoujo_dtor(&this->base);
    this->atk = 0;
    free(this);
}

void Mahoushoujo_do_wish(void *this)
{
    Mahoushoujo *ans = this;
    printf("%s But nothing is good\n", ans->base.wish);
    ans->base.kimoji -= 10;
    return;
}

void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy)
{
     
}

void Mahoushoujo_despair(void *this)
{
    printf("Watashii de, hondo baga\n");
    mhsj_to_mj(this); //turn itself to Mojo????
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
    Shoujo_dtor(&this->base);
    this->atk = 0;
    free(this);
}

/*void Majo_attack(Majo *this, Entity *enemy)
{
    
}*/

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

/*void Madoka_skill(void *this, void *target)
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
        //is_dead
}*/
