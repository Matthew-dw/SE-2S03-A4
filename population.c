#include "a4.h"

#define data(row, col) data[row*width + col]

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
