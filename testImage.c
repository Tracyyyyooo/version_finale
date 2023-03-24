#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"


int main(){
    //create_im(128, "../motif2.png", 255);

    bwimage_t *image = E3ACreateImage();
    bwimage_t *forme = E3ACreateImage();
    bwimage_t *retour;
    bwimage_t *a;

    E3ALoadImage("../image.png", image);
    E3ALoadImage("../motif2.png", forme);
    motif(forme);
    //add_square(forme, 60, 60, 8, 255, "../motif2.png");
    //add_square(image, 10, 40, 32, 255, "../image.png");

    //test general
    
    int x, y;

    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(forme);

    fourier(imC, 1);
    fourier(motifC, 1);
    derive(imC);
    derive(motifC);
   
    image_c *autocorr = correlation(motifC, motifC); //autorrelation du motif
    image_c *retourC = correlation(imC, motifC);

    fourier(autocorr, -1);
    fourier(retourC, -1);
    fourier(imC,-1);
    fourier(motifC,-1);

    float max = autocorr->rawdata[cherchermax(*autocorr)].re;
    int position = chercher_proche(*retourC, max);    //cherche le plus proche de l'autocrorrelation
    x=position%retourC->width;
    y=position/retourC->height;
    printf("Le carée est trouvé dans la position : %d, %d\n", x, y);

    retour = imComplex2Reel(retourC);
    image = imComplex2Reel(imC);
    forme = imComplex2Reel(motifC);
    E3ADumpImage("../retour.png", retour);
    E3ADumpImage("../imD.png", image);
    E3ADumpImage("../motifD.png", forme);



    E3AFreeImage(image);
    E3AFreeImage(forme);
    E3AFreeImage(retour);



//test motif
    /*
    affiche_im(forme);
    bwimage_t *mot = motif(forme);
    affiche_im(mot);
    E3AFreeImage(mot);
    */


    //test derive
    /*
    affiche_im(image);
    image_c *imageC = imReel2Complex(image);
    fourier(imageC, 1);
    derive(imageC);
    fourier(imageC, -1);
    retour = imComplex2Reel(imageC);
    
    affiche_im(retour);
    E3ADumpImage("../retour.png", retour);
    */



    /*
    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(motif);
    */

    /*
    affiche_im_c(imC);
    printf("\n");
    affiche_im_c(motifC);
    */
    /*fourier(testC, 1);
    fourier(testC, -1);*/

    
}