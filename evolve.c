#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sorts in ascending order
int comparator(const void *p, const void *q) { 
    double l = ((Individual *)p)->fitness; 
    double r = ((Individual *)q)->fitness;  
    return (l - r); 
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate) {
    //Take in parameters
    int height = image->height, width = image->width, max_color = image->max_color;
    //Generate Population
    Individual *population = generate_population(population_size, width, height, max_color);
    //Compute Fitness
    comp_fitness_population(image->data, population, population_size);
    //Sort population
    qsort(population, population_size, sizeof(*population), comparator);
    for (int i = 1; i < num_generations; i++) {
        //crossover, mutate then resort
        crossover(population, population_size);
        mutate_population(population, population_size, rate);
        comp_fitness_population(image->data, population, population_size);
        qsort(population, population_size, sizeof(*population), comparator);
    }
    //Free data from images
    for (int i = 1; i < population_size; i++)
        free(population[i].image.data);

    //Make copy of best image before destroying population
    PPM_IMAGE *final_image = malloc(sizeof(PPM_IMAGE));
    memcpy(final_image, &(population[0].image), sizeof(PPM_IMAGE));
    final_image->data = population[0].image.data;

    free(population);
    
    return final_image;
}

void free_image(PPM_IMAGE *p) { free(p->data), free(p); }

