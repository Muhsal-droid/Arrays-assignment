#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "array.h"

struct Performance *newPerformance(){

    struct Performance *performance1 = malloc(sizeof(struct Performance));
    performance1->reads = 0;
    performance1 ->writes  = 0;
    performance1 ->mallocs = 0;
    performance1->frees = 0;
    // this is a function where I am setting everything to 0 and allocating memory
    if (performance1 == NULL){
        fprintf(stderr," malloc has failed and no data is being stored");
        exit (-1);
    }
    return performance1;
}

struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity ){

    struct Array *newarray = malloc(sizeof(struct Array));
    newarray->width = width;
    newarray->capacity = capacity;
    newarray->nel = 0;
    newarray->data = malloc(width*capacity);
    performance->mallocs += 1;
    // this function is allocation sufficient memory for the array structure
    if (newarray == NULL){
        fprintf(stderr," malloc has failed and no data is being stored");
        exit (-1);
    }
    return newarray;
}

void readItem( struct Performance *performance, struct Array *array, unsigned int index, void *dest ){
    unsigned int indexcounter = index ;
     indexcounter*= array->width;
     unsigned char * string = array->data;
    if ( index >= array->nel){
        fprintf(stderr,"index is greater than or equal to array");
        exit (-1);
    // this function copies a certain amount of bytes to memory given by dest
    }else
    {
        memcpy(dest,(string + indexcounter), array->width);
    }

    performance->reads += 1; 
}
void writeItem( struct Performance *performance, struct Array *array, unsigned int index, void *src){
    unsigned int indexcounter = index;
     indexcounter *= array->width;
     unsigned char * line = array->data;

    if ( index > array->nel || index >= array->capacity){
        fprintf(stderr,"index exceeds number of elements or the array capacity");
       exit (-1);
     // this function copies a certain amount of bytes from memory given by src and to array->data
    }else
    {
        memcpy(( line + indexcounter),src,array->width );
    }
        if(index == array->nel){
            array->nel += 1;
        }
        performance->writes += 1;

}
void contract( struct Performance *performance, struct Array *array){

    if (array->nel ==0)
    {
        fprintf(stderr," Elements is equal to the value 0");
        exit (-1);
        
    }else
    {
        array->nel -= 1;
    }
     // this function decrements value of nel if same elements exits or an element is a duplicate
    
}
void freeArray( struct Performance *performance, struct Array *array){
    free(array->data);
    free(array);
    performance->frees +=1;
     // this function frees memory that was initially allocated
}
void appendItem( struct Performance*performance, struct Array *array, void *src){
writeItem( performance,array,array->nel,src);
}
void insertItem(struct Performance *performance, struct Array *array, unsigned int index, void *src){
    int i  = array->nel;
    unsigned char *dest = malloc(array->width);
    unsigned int temp = array->nel;
    while ( i > index)
    {
        temp-=1;
        readItem( performance,array,temp,dest);
        writeItem( performance,array,i,dest);
        i--;
    }
    writeItem( performance,array,index,src);
    free(dest);
     // this function inserts an element to a given place 
    }
void prependItem(struct Performance *performance, struct Array *array, void *src){
    insertItem(performance,array, 0,src);
 // this function inserts ite at the position 0
}
void deleteItem(struct Performance *performance, struct Array *array, unsigned int index){
int i  = array->nel;
unsigned char *src = malloc(array->width);
 unsigned int temp = index;
    unsigned int temp2 = index+1;
    while ( temp < i-1)
    {
        readItem( performance,array,temp2,src);
        writeItem( performance,array,temp,src);
        temp2 += 1;
        temp++;
    }
    contract( performance,array);
    free(src);
     // this function deletes a duplicate  after putting it last by using contract
}
int findItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){
int i = 0;
unsigned char *src = malloc(array->width);
while(i < array->nel){
    readItem( performance,array,i,src);
    int compare1 =compar(src,target);
    if (compare1== 0){
        free(src);
        return i;
    }
        i++;
}
free(src);
return -1;

}
int searchItem( struct Performance *performance, struct Array *array, int (*compar)(const void *, const void *), void *target ){

int numbersSize = array->nel,mid = 0,low = 0;
int high = numbersSize - 1;
int key = 0;
int mid2;
unsigned char *src = malloc(array->width);
while (high >= low) {
 mid = (high + low) / 2;
 mid2 = mid;
readItem( performance,array,mid,src);
      if (compar(src,target)< key) {
         low = mid + 1;
      }
      else if (compar(src,target)> key) {
         high = mid - 1;
      }
      else {
         mid = mid2;
         free(src);
         return mid;
      }
   }
   free(src);
   return -1; 
   
}

