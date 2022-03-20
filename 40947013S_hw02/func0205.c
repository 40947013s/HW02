#include "myvector.h"

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
        pVector->data.p.distance = a;
        pVector->data.p.angle = b;   
        if(a < 0 || b < 0 || b > 2) return -1;                
    }    
    pVector->type = type;
    return 0;
}

void ctop(const sVector *c, double *distance, double *angle)
{
    double x = c->data.c.x, y = c->data.c.y;
    (*distance) = sqrt(pow(x, 2)+pow(y, 2));
    (*angle) = atan2(y, x)/PI;
}

void ptoc(const sVector *p, double *x, double *y)
{
    double d = p->data.p.distance, a = p->data.p.angle;
    (*x) = d*cos(a*PI), (*y) = d*sin(a*PI);
}

int myvector_print(const sVector *pVector, uint8_t type)
{
    if((type != 1 && type != 2) || pVector == NULL) return -1;
    if(type != pVector->type) 
    {
        double p1, p2;
        if(type == 1) 
        {
            ptoc(pVector, &p1, &p2);
            printf("(%lf, %lf)\n", p1,p2);
        }
        else
        {
            ctop(pVector, &p1, &p2);
            printf("(%lf, %lf-pi)\n", p1, p2*180);            
        }
    }
    else
    {
        if(type == 1) 
            printf("(%lf, %lf)\n", pVector->data.c.x,pVector->data.c.y);
        else 
            printf("(%lf, %lf-pi)\n", pVector->data.p.distance, pVector->data.p.angle);
    }    
    return 0;
}

int myvector_add(sVector *pA, const sVector *pB, const sVector *pC)
{
    if(pA == NULL || pB == NULL || pC == NULL) return -1;
    if(pB->type != 1 && pC->type != 1 && pB->type != 0 && pC->type != 0) return -1;
    if(pB->type == 1 && pC->type == 1)
    {
        double x = pB->data.c.x + pC->data.c.x;
        double y = pB->data.c.y + pC->data.c.y;
        myvector_set(pA, 1, x, y);
    }
    else if(pB->type == 1 && pC->type == 2)
    {
        double c1, c2;
        ptoc(pC, &c1, &c2);
        myvector_set(pA, 1, pB->data.c.x+c1, pB->data.c.y+c2);
    }
    else
    {
        double b1, b2, c1, c2;
        ptoc(pB, &b1, &b2);
        if(pC->type == 1)
        {
            c1 = pC->data.c.x; c2 = pC->data.c.y;
        }
        else ptoc(pC, &c1, &c2);
        sVector *ans = myvector_init();
        myvector_set(ans, 1, b1+c1, b2+c2);
        ctop(ans, &b1, &b2);  
        myvector_set(pA, 2, b1, b2);       
    }
    return 0;    
}

int myvector_inner_product(double *pA, const sVector *pB, const sVector *pC)
{
    if(pB == NULL || pC == NULL) return -1;
    if(pB->type == 1 && pC->type == 1)
    {
        (*pA) = pB->data.c.x*pC->data.c.x+pB->data.c.y*pC->data.c.y; 
    }
    else
    {
        double ab = pB->data.p.angle, ac = pC->data.p.angle;
        double db = pB->data.p.distance, dc = pC->data.p.distance;
        double d, a;
        if(pB->type == 1)
        {            
            ctop(pB, &d, &a); db = d; ab = a;
        }
        else if(pC->type == 1)
        {
            ctop(pC, &d, &a); dc = d; ac = a;
        }        
        (*pA) = db*dc*cos((ab-ac)*PI);
    }
    return 0;
}

int myvector_area(double *pA, const sVector *pB, const sVector *pC)
{
    if(pA == NULL || pB == NULL || pC == NULL) return -1;
    if(pB->type == 1 && pC->type == 1)
    {
        (*pA) = fabs(pB->data.c.x*pC->data.c.y-pB->data.c.x*pC->data.c.y); 
    }
    else
    {
        double db = pow(pB->data.p.distance, 2);
        double dc = pow(pC->data.p.distance, 2);
        double d, a;
        if(pB->type == 1)
        {            
            ctop(pB, &d, &a); db = pow(d, 2);
        }
        else if(pC->type == 1)
        {
            ctop(pC, &d, &a); dc = pow(d, 2);
        }
        double inner;
        myvector_inner_product(&inner, pB, pC);
        (*pA) = fabs(sqrt(db*dc-inner));
    }
    return 0;
}

int myvector_cvp(double *pX, double *pY, const double *pTx, const double *pTy, const sVector *pA, const sVector *pB)
{      
    if(pX == NULL || pY == NULL || pTx == NULL || pTy == NULL || pA == NULL || pB == NULL) return -1;
    double x1 = pA->data.c.x, y1 = pA->data.c.y;
    double x2 = pB->data.c.x, y2 = pB->data.c.y;
    double m, n, det, min = 900000000;
    int32_t position[4][2] = {0, 0, 0, 1, 1, 0, 1, 1};
    int32_t M, N;
    if(pA->type != 1) 
        ptoc(pA, &x1, &y1);
    if(pB->type != 1)
        ptoc(pB, &x2, &y2);
    det = 1.0/(x1*y2-x2*y1);
    m = det * (y2*(*pTx)+(-x2)*(*pTy)); M = m;
    n = det * ((-y1)*(*pTx)+x1*(*pTy)); N = n;
    
    for(int i = 0; i < 4; i++)
    {
        double x = (M+position[i][0])*x1 + (N+position[i][1])*y1;
        double y = (M+position[i][0])*y1 + (N+position[i][1])*y2;
        if(pow(x, 2)+pow(y, 2) < min) 
        {
            min = pow(x, 2)+pow(y, 2);
            m = M+position[i][0]; n = N+position[i][1];
        }
    }
    (*pX) = m * x1 + n * x2;
    (*pY) = m * y1 + n * y2;     
    return 0;
}