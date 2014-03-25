#ifndef VP9_COMMON_VP9_COMMON_DATA_H_
#define VP9_COMMON_VP9_COMMON_DATA_H_

#include "vp9_enums.h"

extern const int b_width_log2_lookup[BLOCK_SIZES];
extern const int b_height_log2_lookup[BLOCK_SIZES];
extern const int mi_width_log2_lookup[BLOCK_SIZES];
extern const int mi_height_log2_lookup[BLOCK_SIZES];
extern const int num_8x8_blocks_wide_lookup[BLOCK_SIZES];
extern const int num_8x8_blocks_high_lookup[BLOCK_SIZES];
extern const int num_4x4_blocks_high_lookup[BLOCK_SIZES];
extern const int num_4x4_blocks_wide_lookup[BLOCK_SIZES];
extern const int size_group_lookup[BLOCK_SIZES];
extern const int num_pels_log2_lookup[BLOCK_SIZES];
extern const TX_SIZE max_txsize_lookup[BLOCK_SIZES];
extern const TX_SIZE max_uv_txsize_lookup[BLOCK_SIZES];
extern const TX_SIZE tx_mode_to_biggest_tx_size[TX_MODES];
extern const BLOCK_SIZE ss_size_lookup[BLOCK_SIZES][2][2];

#endif  // VP9_COMMON_VP9_COMMON_DATA_H_
