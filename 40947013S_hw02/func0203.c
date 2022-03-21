#include "madoka.h"
    
Entity *Entity_ctor(Entity *this)
{
    if(this == NULL) return this;
    this->hp = 100;
    this->is_dead = Entity_is_dead;
    return this;
}

void Entity_dtor(Entity *this)
{
    if(this == NULL) return;
    this->hp = 0;
    return;
}

int Entity_is_dead(void *this)
{
    if(this == NULL) return -1;
    Entity *ans = this;
    return ans->hp <= 0 ? 1 : 0; 
}

Shoujo *Shoujo_ctor(Shoujo *this, const char *name, const char *wish)
{    
    if(this == NULL || name == NULL || wish == NULL) return this;
    Entity_ctor(&(this->base)); 
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
    //this->name = NULL;
    //this->wish = NULL;
    this->kimoji = 0;
    return;
}

int Shoujo_is_despair(void *this)
{
    if(this == NULL) return -1;
    Shoujo *ans = this;
    return ans->kimoji <= -100 ? 1 : 0;
}

void Shoujo_do_wish(void *this)
{
    if(this == NULL) return;
    Shoujo *ans = this;
    puts(ans->wish);
    return;
}

void Shoujo_despair(void *this)
{
    if(this == NULL) return;
    Shoujo *ans = this;
    ans->base.hp = 0;
    return;
}

Mahoushoujo *Mahoushoujo_ctor(Mahoushoujo *this, const char *name, const char *wish, Skill skill)
{
    if(this == NULL) return this;
    Shoujo_ctor(&(this->base), name, wish);
    this->base.despair = Mahoushoujo_despair;
    this->atk = 100;
    this->base.base.hp *= 3;
    this->is_dead = Entity_is_dead;
    this->do_wish = Mahoushoujo_do_wish;
    this->attack = Mahoushoujo_attack;
    this->skill = skill;
    return this;
}

void Mahoushoujo_dtor(Mahoushoujo *this)
{
    if(this == NULL) return;
    Shoujo_dtor(&(this->base));
    this->atk = 0;
    return;
}

void Mahoushoujo_do_wish(void *this)
{
    if(this == NULL) return;
    Mahoushoujo *ans = this;
    puts(ans->base.wish);
    puts("But nothing is good");
    ans->base.kimoji -= 10;
    return;
}

void Mahoushoujo_attack(Mahoushoujo *this, Entity *enemy)
{
    if(this == NULL  || enemy == NULL) return;    
    enemy->hp -= this->atk;
    return;
}

void Mahoushoujo_despair(void *this)
{
    if(this == NULL) return;
    puts("Watashii de, hondo baga");
    return;    
}

Majo *Majo_ctor(Majo *this, const char *name, const char *wish)
{
    if(this == NULL || name == NULL || wish == NULL) return this;
    Shoujo_ctor(&this->base, name, wish);
    this->atk = 10;
    this->is_dead = Entity_is_dead;
    this->base.base.hp *= 50;
    this->attack = Majo_attack;
    this->kekkai = Majo_kekkai;
    return this;
}

void Majo_dtor(Majo *this)
{
    if(this == NULL) return;
    Shoujo_dtor(&(this->base));
    this->atk = 0;
    return;
}

void Majo_attack(Majo *this, Entity *enemy)
{
    if(this == NULL) return;
    enemy->hp -= this->atk;
    return;
}

void Majo_kekkai(Majo *this, Shoujo *sj)
{
    if(this == NULL) return;
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
    /*mj->base = mhsj->base;
    mj->atk = mhsj->atk;*/
    return mj;
}

void Madoka_skill(void *this, void *target)
{
    if(this == NULL || target == NULL) return;
    puts("Madoka become god, end.");
    return;
}

void Homura_skill(void *this, void *target)
{
    if(this == NULL || target == NULL) return;
    Mahoushoujo *Homura = this;
    if(Homura->base.base.hp < 50)
        puts("This round is hopeless, Homura go to next round.");
    return;
}

void Sayaka_skill(void *this, void *target)
{
    if(this == NULL || target == NULL) return;
    Mahoushoujo *Sayaka = this;
    Sayaka->base.base.hp += 30;
    Sayaka->base.kimoji-= 30;
    return;
}

void Kyoko_skill(void *this, void *target)
{
    if(this == NULL || target == NULL) return;
    Mahoushoujo *Kyoko = this;
    Mahoushoujo *tar = target;
    if(tar->skill == Sayaka_skill)
    {
        Kyoko->base.base.hp = 0;
        tar->base.base.hp = 0;
    }
    return;
}
