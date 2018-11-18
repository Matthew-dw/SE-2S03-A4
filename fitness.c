#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "a4.h"

#include <stdio.h>

#define NUM_THREADS 16

typedef struct {
    const PIXEL *image;
    Individual *individual;
    int population_size;
    int image_size;
} comp_fitness_data;


double comp_distance(const PIXEL *A, const PIXEL *B, int image_size) {
    double d = 0.0;

    for (int i = 0; i < image_size; i++) {
        d += pow(A[i].r - B[i].r, 2)
           + pow(A[i].g - B[i].g, 2)
           + pow(A[i].b - B[i].b, 2);
    }

    return sqrt(d);
}

void *comp_fitness_subpopulation(void *thread_arg) {
    comp_fitness_data *args = (comp_fitness_data *) thread_arg;

    // printf("THREAD: %d\n", args->population_size);
    for (int i = 0; i < args->population_size; i++) {
        args->individual[i].fitness = comp_distance(args->image,
                                              args->individual[i].image.data,
                                              args->image_size);
    }


    // free(args);
    pthread_exit(NULL);
    // return;
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size) {
    pthread_t threads[NUM_THREADS];
    comp_fitness_data args[NUM_THREADS];

    // Assuming all individuals in population are of the same resolution
    int image_size = individual[0].image.width * individual[0].image.height;

    int subpopulation_size = population_size / NUM_THREADS;
    int offset = 0;
    // printf("Indiv: %ld\nPop: %ld\n", sizeof(Individual), sizeof(individual[0]));
    for (int i = 0; i < NUM_THREADS; i++) {
        // comp_fitness_data *args = malloc(sizeof(comp_fitness_data));
        args[i].image = image;
        args[i].individual = &individual[offset];
        args[i].population_size = subpopulation_size;
        args[i].image_size = image_size;
        pthread_create(&threads[i], NULL, comp_fitness_subpopulation, (void *)(args+i));
        offset += subpopulation_size;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        // printf("IN MAIN: Thread %d has ended.\n", i);
    }
}