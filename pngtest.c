#include "pngwrap.h"
#include <stdio.h>


int main(){
  unsigned long nn[2]={1,2};
  int ndim=2;
  bwimage_t *image;
  error_e retval=E3A_OK;

  image=E3ACreateImage();
  
  do{
    unsigned int i, j;
    if(E3A_OK != (retval=E3ALoadImage("../imageprojet.png", image))) break;
    /* Just to do something - create a negative */
    for(i=0; i<image->height; i++){
      for(j=0; j<image->width; j++){
        image->data[i][j]=0xff-image->data[i][j];
      }
    }
    for(i=0; i<image->height; i++){
      for(j=0; j<image->width; j++){
        image->data[i][j]=image->data[i][j]-'0';
      }
    }
    //fourn((float)image->data,nn,ndim,1);
    if(E3A_OK != (retval=E3ADumpImage("negative.png", image))) break;
    printf("%dx%d\n", image->width, image->height);
  }while(0);

  switch(retval){
  case E3A_OK:
    break;
  case E3A_ENOFILE:
    fprintf(stderr, "Cannot open file\n");
    break;
  case E3A_EPNGLIB:
    fprintf(stderr, "Internal error of libpng\n");
    break;
  case E3A_ENOMEM:
    fprintf(stderr, "Cannot allocate memory\n");
    break;
  default:
    ;/* Can't happen */
  }
   E3AFreeImage(image);

  return 0;
}