/******************************************
  Author: Abner Chou
  Contact: contact AT abnerchou.me
  Date: 2014-May-08

  Discription: A random function generate
    integers following normal distribution.
  
*******************************************/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/* 
    Would like a semi-open interval [min, max) 
    Link: http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
*/
int random_in_range (unsigned int min, unsigned int max)
{
  int base_random = rand(); /* in [0, RAND_MAX] */
  if (RAND_MAX == base_random) return random_in_range(min, max);
  /* now guaranteed to be in [0, RAND_MAX) */
  int range       = max - min,
      remainder   = RAND_MAX % range,
      bucket      = RAND_MAX / range;
  /* 
    There are range buckets, plus one smaller interval
     within remainder of RAND_MAX 
  */
  if (base_random < RAND_MAX - remainder) {
    return min + base_random/bucket;
  } else {
    return random_in_range (min, max);
  }
}

float next_layer(float prev_num){
    if(random_in_range(0,2) == 0)
        return prev_num + 0.5;
    else
        return prev_num - 0.5;
}

float range_mid(int start, int end){
    return (float)(abs(start+end))/2.0;
}

/*
  Parameter: range from the #start# to the #end#
  TODO: --check start end, shouldn't be equal-- should be checked outside of this function
*/
int nor_rand(int start, int end){
    float pile = range_mid(start, end);
    int curr_layer = abs(start-end);
    while(curr_layer>0){
        pile = next_layer(pile);
        curr_layer--;
    }
    return (int)pile;
}

/*
  Test Main function
*/
// void main(){

//     int i;
//     int count[10]={0,0,0,0,0,0,0,0,0,0};
	
//     srand(time(NULL));
//     for(i=0;i<10000;i++){
//         count[nor_rand(1,10)-1]++;
//     }

//     for(i=0;i<10;i++){
//         printf("%d,",count[i]);
//     }

// }
