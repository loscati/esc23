/*

This program looks at the floating point number 0.01

It's very simple ... just accumulate a counter with 0.01 
and see what you get.

History: Written by Tim Mattson, 09/2023.

*/

#include <stdio.h>

int main()
{
   float dt = 0.01f;
   float sum = 0.0f;

   int Count = 10000;

   for(int i = 0; i<Count;i++){
     sum += dt;
   }

   printf(" sum = %f or %f\n",sum,dt*Count);

}
