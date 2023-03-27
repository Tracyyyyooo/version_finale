#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"



int main(){

    ///// en commentaire ce sont les fonctions qui permettent de créer une image de test et son motif
/*
    create_im(128, "../noa.png", 1);
    create_im(128, "../noa_motif.png", 0);
*/

    bwimage_t *image = E3ACreateImage();
    bwimage_t *forme = E3ACreateImage();
    bwimage_t *retour;
    E3ALoadImage("../noa.png", image);
    E3ALoadImage("../noa_motif.png", forme);


//  add_square(forme, 59, 59, 10, 130, "../noa_motif.png"); // motif recherché: carré gris de taille 10
    motif(forme);

/*
    // on rappelle le prototype: add_square(x, y, taille, couleur, adresse);
    // la fonction prenant les coordonnée du coin en haut à gauche, on précise les coordonées de leur centre en commentaire.

    add_square(image, 75, 35, 10, 130, "../noa.png"); //celui de la meme couleur meme taille en 80 40
    
    add_square(image, 20, 50, 10, 0, "../noa.png"); //celui de meme taille en 25 55

    // autres carrés choisis aléatoirement
    add_square(image, 0, 7, 16, 0, "../noa.png");  // 8 15
    add_square(image, 15, 85, 30, 130, "../noa.png"); // 30 100
    add_square(image, 110, 90, 5, 0, "../noa.png"); // 112 92
    add_square(image, 50, 90, 5, 130, "../noa.png"); // 52 92
*/

    

    

    //test general
    //en commentaire ce sont les retours sur l'image et motif dérivés
    

    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(forme);

    fourier(imC, 1);
    fourier(motifC, 1);

    derive(imC);
    derive(motifC);
   
    image_c *autocorr = correlation(motifC, motifC); // autocorrelation du motif
    image_c *retourC = correlation(imC, motifC); // intercorrrélation de l'image et du motif

    fourier(autocorr, -1);
    fourier(retourC, -1);
/*
    fourier(imC, -1);
    fourier(motifC, -1);
*/


    positions(autocorr, retourC);

    retour = imComplex2Reel(retourC);
/*
    image = imComplex2Reel(imC);
    forme = imComplex2Reel(motifC);
*/

    E3ADumpImage("../retour.png", retour);
/*
    E3ADumpImage("../imD.png", image);
    E3ADumpImage("../motifD.png", forme);
*/



    E3AFreeImage(image);
    E3AFreeImage(forme);
    E3AFreeImage(retour);
    

    
}