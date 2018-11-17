#include "a4.h"
#include <stdlib.h>
#include <math.h>

#define data(row, col) data[row * width + col]

PIXEL *generate_random_image(int width, int height, int max_color) {
    PIXEL *data = malloc(sizeof(PIXEL) * width * height);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            data(row, col).r = rand() % (max_color + 1);
            data(row, col).g = rand() % (max_color + 1);
            data(row, col).b = rand() % (max_color + 1);
        }
    }

    return data;
};

Individual *generate_population(int population_size, int width, int height, int max_color) {
    Individual *population = malloc(sizeof(Individual) * population_size);

    for (int i = 0; i < population_size; i++) {
        PPM_IMAGE *image = malloc(sizeof(PPM_IMAGE));
        image->width = width;
        image->height = height;
        image->max_color = max_color;
        image->data = generate_random_image(width, height, max_color);

        population[i].image = *image;
        population[i].fitness = 0.0;
    }

    return population;
}