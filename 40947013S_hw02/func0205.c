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
    if(x == 0 && y == 0) (*angle) = 0;
    else if(x > 0 && y == 0) (*angle) = 0;
    else if(x == 0 && y > 0) (*angle) = 90;
    else if(x < 0 && y == 0) (*angle) = 180;
    else if(x == 0 && y < 0) (*angle) = 270;
    else (*angle) = atan2(y, x)*180/PI;
}

void ptoc(const sVector *p, double *x, double *y)
{
    double d = p->data.p.distance, a = p->data.p.angle;
    if(a == 0.0) (*x) = d, (*y) = 0;
    else if(a == 90.0) (*x) = 0, (*y) = d;
    else if(a == 180.0) (*x) = -d, (*y) = 0;
    else if(a == 270.0) (*x) = 0, (*y) = -d;
    else (*x) = d*cos(a*PI/180), (*y) = d*sin(a*PI/180);
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
            printf("(%lf, %lf)\n", p1,p2);
        }
        else
        {
            ctop(pVector, &p1, &p2);
            if(p2 > 0)
                printf("(%lf, %lf-pi)\n", p1, p2/180.0);
            else
                printf("(%lf, 0-pi)\n", p1);                
        }
    }
    else
    {
        if(type == 1) 
            printf("(%lf, %lf)\n", pVector->data.c.x,pVector->data.c.y);
        else if(pVector->data.p.angle > 0)
            printf("(%lf, %lf-pi)\n", pVector->data.p.distance,pVector->data.p.angle/180.0);
        else printf("(%lf, 0-pi)\n", pVector->data.p.distance);
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
            double b1, b2, c1, c2;
            ptoc(pB, &b1, &b2);
            ptoc(pC, &c1, &c2);
            sVector *ans = myvector_init();
            myvector_set(ans, 1, b1+c1, b2+c2);
            ctop(ans, &pA->data.c.x, &pA->data.c.y);            
        }
        return 0;
    }
    return -1;
    
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
        (*pA) = db*dc*cos((ab-ac)*PI/180);
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