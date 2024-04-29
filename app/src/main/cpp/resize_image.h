#ifndef __RESIZE_IMAGE_H__
#define __RESIZE_IMAGE_H__

int resize_frame_init(int in_width, int in_height, int in_channel, int out_width, int out_height, int out_channel);

int resize_one_frame(unsigned char* in_data[3], unsigned char* out_data[3]);

#endif