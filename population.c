#include "a4.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define data(row, col) data[row * width + col]

#define NUM_THREADS 16

typedef struct {
    Individual *population;
    int population_size;
    int width;
    int height;
    int max_color;
} generate_data;

PIXEL *generate_random_image(int width, int height, int max_color, unsigned int seed) {
    PIXEL *data = malloc(sizeof(PIXEL) * width * height);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            data(row, col).r = rand_r(&seed) % (max_color + 1);
            data(row, col).g = rand_r(&seed) % (max_color + 1);
            data(row, col).b = rand_r(&seed) % (max_color + 1);
        }
    }

    return data;
}

void *generate_subpopulation(void *thread_arg) {
    unsigned int seed = time(NULL);
    generate_data *args = (generate_data *) thread_arg;
    // printf("THREAD: %d\n", args->population_size);
    for (int i = 0; i < args->population_size; i++) {
        PPM_IMAGE *image = malloc(sizeof(PPM_IMAGE));
        image->width = args->width;
        image->height = args->height;
        image->max_color = args->max_color;
        image->data = generate_random_image(args->width, args->height, args->max_color, seed);

        args->population[i].image = *image;
        args->population[i].fitness = 0.0;
    }

    pthread_exit(NULL);
}

Individual *generate_population(int population_size, int width, int height, int max_color) {
    Individual *population = malloc(sizeof(Individual) * population_size);

    pthread_t threads[NUM_THREADS];
    generate_data args[NUM_THREADS];

    int subpopulation_size = population_size / NUM_THREADS;
    int offset = 0;
    // printf("Indiv: %ld\nPop: %ld\n", sizeof(Individual), sizeof(individual[0]));
    for (int i = 0; i < NUM_THREADS; i++) {
        // comp_fitness_data *args = malloc(sizeof(comp_fitness_data));
        args[i].population = &population[offset];
        args[i].population_size = subpopulation_size;
        args[i].width = width;
        args[i].height = height;
        args[i].max_color = max_color;
        pthread_create(&threads[i], NULL, generate_subpopulation, (void *)(args+i));
        offset += subpopulation_size;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        // printf("IN MAIN: Thread %d has ended.\n", i);
    }

    return population;
}