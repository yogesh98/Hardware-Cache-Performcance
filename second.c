#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
  FILE *timeOut;
  timeOut = fopen("timeOut.csv","w");
  int size = 1024*1024;
  char* arr = (char*)malloc(size*sizeof(char));
  long double t;
  long double start;
  long double end;
  double i;
  int j;

  for(j = 0; j<size;j++){
    arr[j]='a'+(rand()%52);
  }

  for(i = .128; i<=10; i+=.128){
    start = clock();
    for(j = 0; j<(i*1024*1024); j++){
      //just so that it accesses the info and does something with it
      arr[j]= arr[j]<<0;
      arr[j]= arr[j]>>0;
    }
    end = clock();
    t = (end-start)/CLOCKS_PER_SEC*1000;
    printf("%f\t%Lf\n", i*1000 , t);
    fprintf(timeOut,"%f,%Lf\n", (i*1000) , t);
  }
}
