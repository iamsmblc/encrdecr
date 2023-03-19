#include "lodepng.h"

#include <stdio.h>
#include <string.h>
#include<time.h>
#include<stdlib.h>

int secMes_func(char message[])
{
int p;//p is 'for' loop variable

gets(message);
printf("Message lenght:%d\n",strlen(message));
if(strlen(message)>255 || strlen(message)==0 ){
    printf("Please enter a string with lenght1-255:");
    secMes_func(message);
}
else{
	printf("Message array before encryiption:[ ");
	for(p=0;p<strlen(message);p++){
		printf("%d ",message[p]);
	}
	printf("]\n");
	
}

return (const char)*message;

}//End of secMes_func function

int target_func(int lenofmes){
    srand(time(NULL));
    int target;
    target=rand()%255 ;
    if(lenofmes==target)//target red and length of a secret message check if equal or not
	{
            target=rand()%255;

    }
    else return target;
    

}//End of target_func function

int arr_func(int arrTest[],int size)//arr_func is the random array generated up to the length of the message.
{

srand(time(NULL));
      int i,j,k,temp,m;

      arrTest[0]=rand()%255;
      for(i=1;i<size;i++){
         arrTest[i]=rand()%255;
         if(i!=0){
            for(m=(i-1);m>=0;m--){
                if(arrTest[i]==arrTest[m]){
                    i--;
                    break;
                }
                else continue;
            }


    }
}//Provides different numbers to be generated each time



      for(j=1;j<size;j++)
{
for(k=1;k<size;k++)
{
    if(arrTest[k-1]>arrTest[k]){
        temp=arrTest[k-1];
        arrTest[k-1]=arrTest[k];
        arrTest[k]=temp;
            }
}



}//sort the array from small to large with bubble sort

printf("Random array before encyription:[ ");
for(k=0;k<size;k++){
	printf("%d ",arrTest[k]);
}
printf("]");



return 0;


  }//End of arr_func function




void decodeOneStep(const char* filename)
{
  
 
  unsigned error;
  unsigned char* image;
 
  unsigned width, height;
  

  error = lodepng_decode24_file(&image, &width, &height, filename);
  
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));//Read message information
  
  char hiddenMessage[255];//Array generated for hidden message in encyription.
  
 secMes_func(hiddenMessage);
   
 target_func(strlen(hiddenMessage));
 
 int blue_arr[255];//Blue values of the image array to be replaced by random array in encyription.
 
 arr_func(blue_arr,strlen(hiddenMessage));
 
 int targetRed_encyr=target_func(strlen(hiddenMessage));//targetRed_encyr, target_func result number.
 
 
  
  int d=3,a;//a,d are 'for' loop variable
  srand(time(NULL));
  
  for(a=3;a<width*height*3;a++){//Since we will use image[0] image[1] to key, a starts from 3.
  if(a%3==0){//The R values in RGB are i% 3 = 0 for image [i]
 
  	if(image[a]==targetRed_encyr){
  		
  		
  		image[a]--;
  		
	  }
	  
	  
	  }
  }
  
  
   
      int b,h,randomPix[255];//b and h are 'for' loop variable.

      randomPix[0]=rand()%(width*height*3);//Red values ??as different as the size of the message was found in the image
     for(b=0;b<strlen(hiddenMessage);b++){
         randomPix[b]=rand()%(width*height*3);
         if(randomPix[b]%3==0){
                 if(b!=0){
            for(h=(b-1);h>=0;h--){
                if(randomPix[b]==randomPix[h] ){
                        
                    b--;
                    break;
                }
                else continue;
            }

            
         }
        

    }
    else b--;
}//Provides different Red values to be generated each time.
	  
	  
	  
	  
	  
	
	
	for(b=0;b<strlen(hiddenMessage);b++){
              
    
	
	image[randomPix[b]]=targetRed_encyr;
	 
	  
	
   	image[randomPix[b]+1]=hiddenMessage[b];//The assignment of hiddenMessage is made in ASCII.

	  
	image[randomPix[b]+2] =blue_arr[b];
	
	 
	  
	  	
	  	
	  

	}
   image[0]=strlen(hiddenMessage);
   image[1]=targetRed_encyr;//Key values for decryption were put to pixel (0,0).
   
   printf("\nYour message is succesfully encyripted!");
   
   
   
  error = lodepng_encode24_file(filename, image, width, height);

  
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));//Changes to the image have been saved with these.
	
	  free(image);
}



int main(int argc, char *argv[])
{
	printf("Enter the message you want to hide(Must  be 1-255):");
  const char* filename = argc > 1 ? argv[1] : "image.png";

  decodeOneStep(filename);

  return 0;
}
