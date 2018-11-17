#include "a4.h"
#include <stdlib.h>
#include <math.h>

#define data(row, col) data[row * width + col]

static int mutate_color(int curr, int max_color){
    curr += (rand() % 100 - 50);
    if (curr > max_color) curr -= max_color;
    if (curr < 0) curr += max_color;
    return curr;
}

void mutate(Individual *individual, double rate){
    PPM_IMAGE image = individual->image;
    PIXEL *data = image.data;
    int height = image.height, width = image.width;
    int max_color = image.max_color;
    
    int n = width * height, pixToChange = (int)(rate/100*n);
    
    for (int i = 0;i < pixToChange;i++){
        int row = rand() % height + 1;
        int col = rand() % width + 1;

        data(row, col).r = mutate_color(data(row, col).r, max_color);
        data(row, col).g = mutate_color(data(row, col).g, max_color);
        data(row, col).b = mutate_color(data(row, col).b, max_color);
    }
}

void mutate_population(Individual *individual, int population_size, double rate){
    //Only mutating from pop/4 to pop-1
    int i = (int)population_size/4;
    for (i;i < population_size;i++){
        mutate(individual + i, rate);
    }
}
