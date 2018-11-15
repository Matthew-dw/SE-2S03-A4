#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

#define data(row, col) image->data[row*image->width + col]

PPM_IMAGE *read_ppm(const char *file_name) {
    FILE *file = fopen(file_name, "r"); 
    PPM_IMAGE *image = malloc(sizeof(PPM_IMAGE));

    fscanf(file, "%*s\n");  // Ignore format string
    fscanf(file, "%d %d\n", &image->width, &image->height);     
    fscanf(file, "%d\n", &image->max_color);

    image->data = malloc(sizeof(PIXEL) * image->width * image ->height);

    for (int row = 0; row < image->height; row++) {
        for (int col = 0; col < image->width; col++) {
            fscanf(file, "%hhd %hhd %hhd ", 
                            &data(row, col).r, 
                            &data(row, col).g, 
                            &data(row, col).b );
        }
        fscanf(file, "\n");
    }

    fclose(file);
    return image;
};

void write_ppm(const char *file_name, const PPM_IMAGE *image) {
    FILE *file = fopen(file_name, "w");

    fprintf(file, "%s\n", "P3");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->max_color);

    for (int row = 0; row < image->height; row++) {
        for (int col = 0; col < image->width; col++) {
            fprintf(file, "%d %d %d ", 
                            data(row, col).r, 
                            data(row, col).g, 
                            data(row, col).b );
        }
        fprintf(file, "\n");
    }

    fclose(file);
};

// int main() {
//     PPM_IMAGE *image = read_ppm("me.ppm");
//     write_ppm("test.ppm", image);

//     return 0;
// }