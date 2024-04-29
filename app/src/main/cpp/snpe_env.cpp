#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include "android_log.h"

bool setAdspLibraryPathC(std::string& nativeLibPath)
{
    std::stringstream path;

    LOGI("dsp env:%s", nativeLibPath.c_str());

    path << nativeLibPath << ";/system/lib/rfsa/adsp;/system/vendor/lib/rfsa/adsp;/dsp;/system/vendor/lib";
    bool bRet = setenv("ADSP_LIBRARY_PATH", path.str().c_str(), 1 /*override*/) == 0;
    return  setenv("LD_LIBRARY_PATH", path.str().c_str(), 1 /*override*/) == 0;
}