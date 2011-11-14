

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>                  /*  for sleep()  */


int main(void) {


    fprintf(stderr,"\033[%d;%dH",13,33);
printf("hello world\n");


    return EXIT_SUCCESS;
}
