#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265
#define VAL 180.0/PI 

typedef struct _sVector
{
    uint8_t type;
    union Component
    {
        struct _sCartesian
        {
            double x;
            double y;
        } c;
        struct _sPolar
        {
            double distance;
            double angle;
        } p;
    } data;
}sVector;

sVector *myvector_init()
{
    sVector *res = (sVector *)calloc(1, sizeof(sVector *));
    res->type = 0;
    res->data.c.x = 0;
    res->data.c.y = 0;
    res->data.p.distance = 0;
    res->data.p.angle = 0;
}

int myvector_set(sVector *pVector, uint8_t type, double a, double b)
{
    if((type != 1 && type != 2) || pVector == NULL) return -1;
    else if(type == 1) 
        pVector->data.c.x = a, pVector->data.c.y = b;
    else
    {
        while(b < 0) b+= 360;
        while(b >= 360) b-= 360;
        pVector->data.p.distance = a;
        pVector->data.p.angle = b;   
        if(a < 0) return -1;                
    }    
    pVector->type = type;
    return 0;
}

void ctop(const sVector *c, double *distance, double *angle)
{
    double x = c->data.c.x, y = c->data.c.y;
    (*distance) = sqrt(pow(x, 2)+pow(y, 2));
    (*angle) = atan(x/y)*VAL;
}

void ptoc(const sVector *p, double *x, double *y)
{
    double d = p->data.p.distance, a = p->data.p.angle;
    //printf("%lf\n", a);
    if(a == 0.0) (*x) = d, (*y) = 0;
    else if(a == 90.0) (*x) = 0, (*y) = d;
    else if(a == 180.0) (*x) = -d, (*y) = 0;
    else if(a == 270.0) (*x) = 0, (*y) = -d;
    else (*x) = d*cos(a*VAL), (*y) = d*sin(a*VAL);
    //printf("%lf %lf %lf\n", a, cos(a*VAL), sin(a*VAL));
}

int myvector_print(const sVector *pVector, uint8_t type)
{
    if(pVector == NULL) return -1;
    if(type != pVector->type) 
    {
        double p1, p2;
        if(type == 1) 
        {
            ptoc(pVector, &p1, &p2);
            printf("(%g, %g)\n", p1,p2);
        }
        else
        {
            ctop(pVector, &p1, &p2);
            printf("(%g, %g-pi)\n", p1, p2/180.0);
        }
    }
    else
    {
        if(type == 1) 
            printf("(%g, %g)\n", pVector->data.c.x,pVector->data.c.y);
        else
            printf("(%g, %g-pi)\n", pVector->data.p.distance,pVector->data.p.angle/180.0);
    }    
    return 0;
}

int myvector_add(sVector *pA, const sVector *pB, const sVector *pC)
{
    if(pA == NULL || pB == NULL || pC == NULL) return -1;
    pA->type = pB->type;
    if(pB->type == pC->type)
    {
        if(pB->type == 1)
        {
            pA->data.c.x = pB->data.c.x + pC->data.c.x;
            pA->data.c.y = pB->data.c.y + pC->data.c.y; 
        }
        else
        {
            
        }
        return 0;
    }
    return -1;
    /*if(pB->type == pC->type == 1)
    {
        pA->data.c.x = pB->data.c.x + pC->data.c.x;
        pA->data.c.y = pB->data.c.y + pC->data.c.y;   
    }
    else if(pB->type == pC->type == 2)
    {
        double x = pB->data.p.distance*cos(pB->data.p.angle*VAL) + pC->data.p.distance*cos(pC->data.p.angle*VAL);
        double y = pB->data.p.distance*sin(pB->data.p.angle*VAL) + pC->data.p.distance*sin(pC->data.p.angle*VAL);
        pA->data.p.distance = sqrt(pow(x, 2)+pow(y, 2));
        pA->data.p.angle = atan(x/y)*VAL;
    }*/
}

int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC)
{
    if(pB == NULL || pC == NULL) return -1;
    if(pB->type == pC->type)
    {
        if(pB->type == 1)
            (*pA) = pB->data.c.x*pC->data.c.x+pB->data.c.y*pC->data.c.y; 
        else
        {
            double angle = pB->data.p.angle-pC->data.p.angle;
            (*pA) = pB->data.p.distance*pC->data.p.distance*cos(angle*VAL);
        }
        return 0;
    }
    return -1;
}

int myvector_area(double *pA, const sVector *pB, const sVector *pC)
{
    if(pB == NULL || pC == NULL) return -1;
    if(pB->type == pC->type)
    {
        if(pB->type == 1)
            (*pA) = pB->data.c.x*pC->data.c.y-pB->data.c.x*pC->data.c.y; 
        else
        {
            double db = pB->data.p.distance;
            double dc = pc->data.p.distance;
            double inner_product;
            myvector_inner_product(&inner_product, pB, pC);
            (*pA) = sqrt(db*dc-inner_product);
        }
        return 0;
    }
    return -1;
}

int myvector_cvp(double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB)
{
    if(pB->type == pC->type == 1)
    {
        int lm = 0, ln = 0, rm = 0, rn = 0, i = 0, j = 0;
        double ans_x = 0, ans_y = 0;
        while(ans_x <= *pTx || ans_y <= *pTy)
        {
            ans_x = i*pA->data.c.x*i + i*pB->data.c.x*j;
            ans_y = i*pA->data.c.y*i + i*pB->data.c.y*j;
            i++;
        } lm = i;
        while(ans_x <= *pTx && ans_y <= *pTy)
        {
            ans_x = i*pA->data.c.x*i + i*pB->data.c.x*j;
            ans_y = i*pA->data.c.y*i + i*pB->data.c.y*j;
            i++;
        } rm = i;
        while(ans_x <= *pTx || ans_y <= *pTy)
        {
            ans_x = i*pA->data.c.x*i + i*pB->data.c.x*j;
            ans_y = i*pA->data.c.y*i + i*pB->data.c.y*j;
            j++;
        } ln = j;
        while(ans_x <= *pTx && ans_y <= *pTy)
        {
            ans_x = i*pA->data.c.x*i + i*pB->data.c.x*j;
            ans_y = i*pA->data.c.y*i + i*pB->data.c.y*j;
            j++;
        } rn = j;
        for(int i = lm-1; i <= rm; i++)
        {
            for(int j = ln-1; j <= lm; j++)
            {
                ans_x = i*pA->data.c.x*i + i*pB->data.c.x*j;
                ans_y = i*pA->data.c.y*i + i*pB->data.c.y*j;
                if()
            }
        }
    }
}

int main()
{
    sVector *ans = myvector_init();
    sVector *one = myvector_init();
    sVector *two = myvector_init();
    myvector_set(one, 2, 5, 45);
    double x, y;
    ptoc(one, &x, &y);
    printf("%lf %lf\n", x, y);
    myvector_print(one, 1);
    
    myvector_set(two, 1, 3, 4);
    double r, a;
    ctop(two, &r, &a);
    printf("%lf %lf\n", r, a);
    myvector_print(two, 2);

}