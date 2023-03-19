#include "lodepng.h"

#include <stdio.h>
#include <stdlib.h>

int sort_func(int sort_randArr[],int sort_messArr[],int sortSize){
    int m,n,temp,temp2;



for(n=1;n<sortSize;n++){//The values in the sort_randArr and sort_messArr array are sorted from small to large with bubble sort.
  for(m=1;m<sortSize;m++){
    if(sort_randArr[m-1]>sort_randArr[m]){
        temp=sort_randArr[m-1];
      	sort_randArr[m-1]=sort_randArr[m];
		sort_randArr[m]=temp;
		
		
        temp2=sort_messArr[m-1];
		sort_messArr[m-1]=sort_messArr[m];
        sort_messArr[m]=temp2;
            }
  }
 } //The order sort_messArr  of is in ASCII.
}


void decodeOneStep(const char* filename)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;

  error = lodepng_decode24_file(&image, &width, &height, filename);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

  int size=image[0];//Size is length of the hidden message encrypted.
  int targetRed=image[1];//targetRed value we use to find the secret message.
  
  int messArrDecyr[255];
  int randArrDecyr[255];
  //Above arrays are for each value of the hidden message, we use the arrays in the decryption phase.
  int d=0,i,k;
 for(i=3;i<width*height*3;i++)
 {
 	    if(i%3==0){
 		if(image[i]==targetRed){
		messArrDecyr[d]=image[i+1];
 		randArrDecyr[d]=image[i+2];
 		d++;
		 }
 		
 		
	 }
 	
 }//End of 'for' loop used to find the secret message and each value of the random.
 printf("Message array before decryption:[");
  for(k=0;k<size;k++){
  	printf("%d  ",messArrDecyr[k]);
  }
  printf("]\n");
  
  printf("Random array before decryption:[");

  for(k=0;k<size;k++){
  	printf("%d  ",randArrDecyr[k]);
  }
  printf("]\n");
  
  sort_func(randArrDecyr,messArrDecyr,size);//With sort_func, the characters of the hidden message are in the correct order.
 
 


printf("The hidden message:");

  for(k=0;k<size;k++){
  	printf("%c",messArrDecyr[k]);
  }//Each value messArrDecyr after bubble sort is listed in characters.
  
  
  
  

  free(image);
}



int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "image.png";

  decodeOneStep(filename);

  return 0;
}
