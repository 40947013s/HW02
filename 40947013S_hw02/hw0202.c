#include "hw0202.h"

int main(void) 
{
    double target = 0;
    printf("Please enter a floating -point number (double precision): ");
    scanf("%lf", &target);
    
    IEEE var;
    change(&var, target);
    printer(var, target);
    return 0;
}