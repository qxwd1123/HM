#ifndef __HW_GLOBAL_H
#define __HW_GLOBAL_H

#include <cassert>
#include <cstdint>
#include <cstring>

#define assertf(x) for (; !(x); assert(x))

typedef struct hw_global_t {
  int32_t frame_idx;
  char *input_fn;
  char *output_fn;
} hw_global_t;

extern hw_global_t *hw_global;

void hw_global_init();

void hw_global_destroy();

void hw_global_set_input_fn(char *input_fn);

void hw_global_frame_next();

void hw_global_frame_done();

#endif
