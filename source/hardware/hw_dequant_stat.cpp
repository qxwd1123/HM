#include "hw_dequant_stat.h"

static coeff_stat tu32_stat = {};

void hw_dequant_stat_init() {}

void hw_dequant_stat_destroy() {}

void hw_dequant_stat_frame_next(int32_t frame_idx) {}

void hw_dequant_stat_frame_done() {
  FILE *fp = fopen(hw_global->output_fn, "w+");
  assertf(fp != NULL)
      fprintf(stderr, "fopen %s output failed\n", hw_global->output_fn);
  fprintf(fp, "total: %d\n", tu32_stat.total);
  fprintf(fp, "upper only: %02.2f\n",
          (double)tu32_stat.upper_only / tu32_stat.total);
  fprintf(fp, "left only: %02.2f\n",
          (double)tu32_stat.left_only / tu32_stat.total);
  fprintf(fp, "upper-left only: %02.2f\n",
          (double)tu32_stat.ul_only / tu32_stat.total);
  fclose(fp);
}

bool is_coeff_empty(const TCoeff *const piCoef) {
  int8_t col, row;
  for (row = 0; row < 16; row++)
    for (col = 0; col < 16; col++)
      if (piCoef[row * 32 + col] != 0) return false;
  return true;
}

void hw_dequant_stat_update_dqcoeff(const UInt uiWidth, const UInt uiHeight,
                                    const TCoeff *const piCoef) {
  uint8_t col_16, row_16;
  uint8_t block_stat[4];
  if (uiWidth == 32 && uiHeight == 32) {
    tu32_stat.total++;
    for (row_16 = 0; row_16 < 2; row_16++)
      for (col_16 = 0; col_16 < 2; col_16++)
        if (is_coeff_empty(piCoef + row_16 * 16 * 32 + col_16 * 16))
          block_stat[row_16 * 2 + col_16] = 1;
        else
          block_stat[row_16 * 2 + col_16] = 0;
    if (block_stat[1] && block_stat[2] && block_stat[3])
      tu32_stat.ul_only++;
    else if (block_stat[2] && block_stat[3])
      tu32_stat.upper_only++;
    else if (block_stat[1] && block_stat[3])
      tu32_stat.left_only++;
  }
}
