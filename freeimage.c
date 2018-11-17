#include "a4.h"
#include <stdlib.h>
void free_image(PPM_IMAGE *p) { free(p->data), free(p); }
