#include <stdio.h>
#include <stdarg.h>


long puzzle7(long a, ...){
   va_list ap;
   int vas = 3;
   long sum = 0;
   va_start(ap, a);
   while(a--)
      sum += va_arg(ap, long);
   va_end(ap);
   return sum;
}

int main(){
    printf("%ld\n", puzzle7(8,10,20,30,40,50,60,70,100,11111));
    return 0;
}