#ifndef __SNPE_LOADER_H__
#define __SNPE_LOADER_H__

#include <cstring>
#include <iostream>
#include <getopt.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <unordered_map>
#include <algorithm>

bool CreateSnpeEngine(std::string& dlc, std::string& runtime, std::string& userbuffer_fmt, bool gpu_buffer,
                             int in_width, int in_height, int in_channel, int out_width, int out_height, int out_channel);

int GetSnpeInputBuffer(void** input, int* in_size);

int SnpeInference(void* input, int in_len, void** output, int* out_len);

void ReleaseSnpeEngine();

#endif
