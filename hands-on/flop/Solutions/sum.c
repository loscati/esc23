/*

NAME:   
   sum

Purpose: 
   Create an array of numbers and explore floating point 
   arithmetic issues as you sum the array

History: 
   Written by Tim Mattson, 9/2023.

*/
#include <stdio.h>
#include <stdlib.h>

#define N 100000  //length of sequence of numbers to work with  

//============================================================================
// support functions
//============================================================================
void seed(float, float);              // seed pseudorandom number generator
float frandom();                      // Get next pseudorandom in the sequence
void FillSequence(float*, float*);    // fill sequence (>0), return "true" sum
float KahanSum(int, float*);          // Kahan Sum of a sequence
int comp(const void *, const void *); // comparator func for qsort

//============================================================================

int main ()
{
   float seq[N];    //Sequence to sum, statically defined to keep the code simple
   float True_sum;  //The best estimate of the actual sum

   FillSequence(seq, &True_sum); // populate seq with random values > 0


   // basic, naive sum
   float sum_val =0.0f;
   for (int i=0; i<N; i++){
       sum_val += seq[i];
   }
   printf(" Basic sum = %f, best estimated sum = %f\n",sum_val,True_sum);

   // Do the Kahan Summation on the original sequence
   sum_val = KahanSum(N, seq);
   printf(" Kahan sum of unsorted sequence = %f, best estimated sum = %f\n",sum_val,True_sum);
   
   // Sort the sequence then sum the sorted sequence
   sum_val = 0.0f;
   qsort(seq, N, sizeof(float), comp);
   for (int i=0; i<N; i++){
       sum_val += seq[i];
   }
   printf(" Basic sum Sorted seq = %f, best estimated sum = %f\n",sum_val,True_sum);

   // Do the Kahan Summation on the sorted sequence
   sum_val = KahanSum(N, seq);
   printf(" Kahan sum of sorted seq = %f, best estimated sum = %f\n",sum_val,True_sum);

}

// sum the sequence, x, of length Nlen using the Kahan algorithm
float KahanSum(int Nlen, float *x)
{
   float ksum, correction, xcorrected, tmpSum;

   if(Nlen < 1) return -1;  // need at least two values to sum

   correction = 0.0f;
   ksum = x[0];
   for (int i = 1; i<Nlen;i++){
      xcorrected = x[i] - correction; 
      tmpSum =  ksum + xcorrected;
      correction = (tmpSum - ksum) - xcorrected;
      ksum = tmpSum;
   }
   return ksum;
}

// Compare pair of floats passed to comparator
// This is used in qsort so I can sort the array before summing.
int comp(const void *p, const void *q) 
{
    float l = *(const float *)p;
    float r = *(const float *)q;
    return l - r;
}

//=================================================================
//  don't worry about (or even look at) anything below this line.  
//=================================================================

//================================================================
//  Function to fill a sequence of N values greater than zero and
//  produce a high quality estimate of the sum of those values
//================================================================
void FillSequence(float *seq, float *True_sum)
{

   float True = 0.0f, val;
   float shift_up   = 100.0f;
   float shift_down =   0.0000000001f;

   seed(0.0, 1.0);
   
   double up_sum   = 0.0d;
   double down_sum = 0.0d;

   for(int i=0;i<N; i++){
     if(i%2==0){
         seq[i]   = (float) frandom() * shift_up;
         up_sum   += (double) seq[i];
     }
     else {
         seq[i]   = (float) frandom() * shift_down;
         down_sum += (double) seq[i];
     }
   }
   
   *True_sum = (float)(up_sum + down_sum);
}
/*

   For maximum portability, this file includes a very simple random number
   generator.  This is not a high quality generator and should not be used
   for serious work.

   The Generator is a linear congruential generator with constants selected
   to yield decent results for sequences with fewer than 2^28 numbers.  The
   pseudo random sequence is seeded with a range

       void seed(lower_limit, higher_limit)
   
   and then subsequent calls to the random number generator generates values
   in the sequence:

       float frandom()
*/

// random number file-scope variables, seed and generator
long random_last = 0.0;
float random_low, random_hi;
void seed(float, float);
float frandom();

//**********************************************************
// Pseudo random number generator:
//     double random
//     void seed (lower_limit, higher_limit)
//**********************************************************
//
// A simple linear congruential random number generator
// (Numerical Recipies chapter 7, 1st ed.) with parameters
// from the table on page 198j.
//
//  Uses a linear congruential generator to return a value between
//  0 and 1, then scales and shifts it to fill the desired range.  This
//  range is set when the random number generator seed is called.
//
static long MULTIPLIER  = 1366;
static long ADDEND      = 150889;
static long PMOD        = 714025;

void seed(float low_in, float hi_in);

float frandom()
{
    long random_next;
    float ret_val;

// 
// compute an integer random number from zero to mod
//
    random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
    random_last = random_next;

//
// shift into preset range
//
    ret_val = ((float)random_next/(float)PMOD)*(random_hi-random_low)+random_low;
    return ret_val;
}

//
// set the seed and the range
//
void seed(float low_in, float hi_in)
{
   if(low_in < hi_in)
   { 
      random_low = low_in;
      random_hi  = hi_in;
   }
   else
   {
      random_low = hi_in;
      random_hi  = low_in;
   }
   random_last = PMOD/ADDEND;  // just pick something

}
//**********************************************************
// end of pseudo random generator code.
//**********************************************************

