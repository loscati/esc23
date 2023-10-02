/*

This program shows how to change rounding modes in a C program.
We do this while exploring simple summations of 0.01.  The 
goal is to explore properties of floating point arithmetic.

History: Written by Tim Mattson, 09/2023.

*/

#include <stdio.h>
#include <fenv.h>

// enable access to control over the floating point environment.
// It will be enabled until it is turned off or until we reach the
// end of this translation unit.
#pragma STCD FENV_ACCESS ON

int main()
{
   float dt = 0.01f;
   float sum = 0.0f;

   // save originial rounding mode
   const int origRound = fegetround();

   // change rounding mode.  Options are FE_DOWNWARD, FE_TOWARDZERO,
   // FE_UPWARD, FE_TONEAREST
   fesetround(FE_DOWNWARD);

   int Count = 10000;

   for(int i = 0; i<Count;i++){
     sum += dt;
   }

   printf(" sum = %f or %f\n",sum,dt*Count);

   // Return to orignial rounding mode.  
   fesetround(origRound);

   for(int i = 0,sum=0.0f; i<Count;i++){
     sum += dt;
   }

   printf(" original model: sum = %f or %f\n",sum,dt*Count);

}
