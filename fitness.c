#include "a4.h"
#include <math.h>

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size) {
    double d = 0.0;
    
    for (int i = 0; i < image_size; i++) {
        d += pow(A[i].r - B[i].r, 2) 
           + pow(A[i].g - B[i].g, 2) 
           + pow(A[i].b - B[i].b, 2);
    }

    return sqrt(d);
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size) {
    for (int i = 0; i < population_size; i++) {
        int image_size = individual[i].image.width * individual[i].image.height; 
        individual[i].fitness = comp_distance(image, individual[i].image.data, image_size);
    }
}