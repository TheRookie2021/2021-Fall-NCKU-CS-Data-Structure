#include <stdio.h>
#include <time.h>

int main() {
   // Calculate the time taken by take_enter()
   clock_t t;
   t = clock();
   int x;
   for(int i=0;i<100000000*3 ;i++){
       x=i*2;
   };
   t = clock() - t;
   double time_taken = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
   printf("The program took %f seconds to execute", time_taken);
}