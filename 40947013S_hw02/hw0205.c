#include "myvector.h"

int main()
{
    sVector *ans = myvector_init();
    sVector *one = myvector_init();
    sVector *two = myvector_init();
    
    myvector_set(one, 1, 12, 5);
    myvector_set(two, 2, 5, 37);
    

    /*myvector_add(ans, one, two);
    myvector_print(ans, 1);
    myvector_print(ans, 2);*/
    
    /*double pA;
    myvector_inner_product(&pA, one, two);
    printf("%lf\n", pA);

    myvector_area(&pA, one, two);
    printf("%lf\n", pA);*/

    /*double pX, pY, tx = 27, ty = 29;
    myvector_cvp(&pX, &pY, &tx, &ty, one, two);
    printf("%lf %lf\n", pX, pY);*/

    
}