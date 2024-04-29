#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "android_log.h"

static int s_scale;
static int s_row_offset, s_col_offset;
static int s_in_width, s_in_height, s_in_channel, s_out_width, s_out_height, s_out_channel;
int resize_frame_init(int in_width, int in_height, int in_channel, int out_width, int out_height, int out_channel)
{
    if (in_channel != 1) {
        return -1;
    }

    //#0 计算scale
    double scale_width = in_width * 1.0 / out_width;
    double scale_height = in_height * 1.0 / out_height;

    double scale = scale_width > scale_height ? scale_width : scale_height;

    //#1 计算offset，row_offset, col_offset
    int row_offset = (out_height - (int)(in_height/scale)) / 2;
    if (row_offset < 0)
        row_offset = 0;
    else if (row_offset >= out_height)
        row_offset = out_height - 1;

    int col_offset = (out_width - (int)(in_width/scale)) / 2;
    if (col_offset < 0)
        col_offset = 0;
    else if (col_offset >= out_width)
        col_offset = out_height - 1;

    s_row_offset = row_offset;
    s_col_offset = col_offset;
    s_scale = (int)(scale * 16384);

    s_in_width = in_width;
    s_in_height = in_height;
    s_in_channel = in_channel;

    s_out_width = out_width;
    s_out_height = out_height;
    s_out_channel = out_channel;

    return 1;
}

int resize_one_frame(unsigned char* in_data[3], unsigned char* out_data[3])
{
    int out_height = s_out_height - 2 * s_row_offset;
    int out_width = s_out_width - 2 * s_col_offset;

    for (int y = 0; y < out_height; y++) {
        for (int x = 0; x < out_width; x++) {
            int val0 = (y * s_scale) >> 14;
            int val1 = (x * s_scale) >> 14;
            int in_pos = val0 * s_in_width + val1;
            int out_pos = (s_row_offset + y) * s_out_width + (s_col_offset + x);

            out_data[0][out_pos] = in_data[0][in_pos];

        }

    }

    return 0;
}
