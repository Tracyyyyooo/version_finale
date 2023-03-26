#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"



int main(){
    
    create_im(128, "../noa.png", 1);
    create_im(128, "../noa_motif.png", 0);

    bwimage_t *image = E3ACreateImage();
    bwimage_t *forme = E3ACreateImage();
    bwimage_t *retour;
    E3ALoadImage("../noa.png", image);
    E3ALoadImage("../noa_motif.png", forme);


    add_square(forme, 59, 59, 10, 130, "../noa_motif.png");
    motif(forme);


    add_square(image, 75, 35, 10, 130, "../noa.png"); //celui de la meme couleur en 80 40
    
    add_square(image, 20, 50, 10, 0, "../noa.png"); //celui de meme taille en 25 55

    add_square(image, 0, 7, 16, 0, "../noa.png");  // 8 15
    add_square(image, 15, 85, 30, 130, "../noa.png"); // 30 100
    add_square(image, 110, 90, 5, 0, "../noa.png"); // 112 92
    add_square(image, 50, 90, 5, 130, "../noa.png"); // 52 92


    

    

    //test general
    
    int x, y;

    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(forme);

    fourier(imC, 1);
    fourier(motifC, 1);
    derive(imC);
    derive(motifC);
   
    image_c *autocorr = correlation(motifC, motifC); //autocorrelation du motif
    image_c *retourC = correlation(imC, motifC);

    fourier(autocorr, -1);
    fourier(retourC, -1);
    fourier(imC, -1);
    fourier(motifC, -1);

    float p = autocorr->rawdata[cherchermax(*autocorr)].re; //trouve la correlation maximum
    int* position = chercherproche(*retourC, p); //cherche le plus proche de p
    for(int i=0; i<5; i++){
        x=position[i]%retourC->width;
        y=position[i]/retourC->height;
        printf("%d, %d\n", x, y);   
    }

    retour = imComplex2Reel(retourC);
    image = imComplex2Reel(imC);
    forme = imComplex2Reel(motifC);
    E3ADumpImage("../retour.png", retour);
    E3ADumpImage("../imD.png", image);
    E3ADumpImage("../motifD.png", forme);



    E3AFreeImage(image);
    E3AFreeImage(forme);
    E3AFreeImage(retour);

    
}
