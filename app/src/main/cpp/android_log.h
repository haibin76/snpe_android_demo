#ifndef __ANDROID_LOG_H__
#define __ANDROID_LOG_H__

#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "JNI SNPE::", __VA_ARGS__))

#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "JNI SNPE::", __VA_ARGS__))

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "JNI SNPE::", __VA_ARGS__))

#endif