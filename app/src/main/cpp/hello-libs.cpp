/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <android/log.h>
#include <SnpeLoader.h>
#include "android_log.h"
#include "resize_image.h"
#include "snpe_env.h"
#include <jni.h>

#include <cinttypes>
#include <cstring>
#include <string>

/*
 * JNI层主要的工作流程包括一下几个方面：
 * 1:对摄像头捕捉的二维码图像做resize，这个模块就是将图像的Y输入JNI，由JNI层先做resize，同时要对图像进行归一化处理
 * 2:将第一步计算出来的图像归一化数据，送入SNPE SDK中，进行推理，将推理的数据保存到memory中，然后将memory送给图像后处理
 * 3:做图像的后处理，处理之后的结果返回给java层
 * 整个过程大概分三个接口，
 * 1:初始化接口，将相关的JNI需要的参数都传递给下来，进行初始化
 * 2:每一帧的推理，整个过程就是循环调用，每次推理就要调用一次
 * 3:等推理结束，app退出的时候，释放掉相关资源
 */

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_hellolibs_MainActivity_setAdspLibraryPath(JNIEnv *env,jobject thiz, jstring j_nativeLibPath)
{
    const char* ch0 = env->GetStringUTFChars(j_nativeLibPath, nullptr);
    std::string nativeLibPath(ch0);

    return setAdspLibraryPathC(nativeLibPath);
}

/*
 *初始化JNI层的C代码，这些初始化的参数主要包括
 * j_in_width:jint,对图像resize之前，输入图像的的宽
 * j_in_height:jint,对图像resize之前，输入图像的高
 * j_in_channel:jint，对图像resize之前，输入图像的channel，目前只支持channel=1的情况
 * j_out_width:jint,对图像resize之后，输出图像的宽，也是进入SNPE SDK的输入宽
 * j_out_height:jint,对图像resize之后，输出图像的高，也是进入SNPE SDK的输入高
 * j_out_channel:jint,对图像resize之后，输出图像的宽，也是进入SNPE SDK的输入chanel
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_hellolibs_MainActivity_initJni(JNIEnv *env,jobject thiz,
                                                jstring j_dlc_file, jstring j_run_time, jstring j_data_fmt,
                                                jboolean j_use_opengl,
                                                jint j_in_width, jint j_in_height, jint j_in_channel,
                                                jint j_out_width, jint j_out_height, jint j_out_channel)
{
    const char* ch1 = env->GetStringUTFChars(j_dlc_file, nullptr);
    std::string dlc_file(ch1);
    const char* ch2 = env->GetStringUTFChars(j_run_time, nullptr);
    std::string run_time(ch2);
    const char* ch3 = env->GetStringUTFChars(j_data_fmt, nullptr);
    std::string data_fmt(ch3);
    bool opengl = j_use_opengl == JNI_TRUE;

    LOGI("initJni is called by java, the parameter:");
    LOGI("dlc file:%s", dlc_file.c_str());
    LOGI("run time:%s", run_time.c_str());
    LOGI("data format:%s", data_fmt.c_str());
    LOGI("the input shape:(%d*%d*%d)", j_in_channel, j_in_width, j_in_height);
    LOGI("the output shape:(%d*%d*%d)", j_out_channel, j_out_width, j_out_height);

    //#0 设置DSP的环境变量

    //#1 调用resize的初始化函数
    int iRet = resize_frame_init(j_in_width, j_in_height, j_in_channel,
                                j_out_width, j_out_height, j_out_channel);
    if (iRet < 0) {
        LOGE("resize_frame_init error");
        return -1;
    }
    LOGI("setting the resize parameters success");

    const char *ldLibraryPath = getenv("LD_LIBRARY_PATH");
    if (ldLibraryPath != NULL) {
        LOGI("LD_LIBRARY_PATH: %s\n", ldLibraryPath);
    } else {
        LOGE("LD_LIBRARY_PATH not set\n");
    }

    //#2 调用snpe sdk的初始化
    iRet = CreateSnpeEngine(dlc_file, run_time, data_fmt, opengl,
                                j_in_width, j_in_height, j_in_channel,
                                j_out_width, j_out_height, j_out_channel);
    if (iRet <= 0) {
        LOGE("CreateSnpeEngine error");
        return -1;
    }
    LOGI("CreateSnpeEngine success");

    return 0;
}

/*
 * 推理函数，每一帧都要调用该函数，将图片中热点定位出来，并且匹配出来，参数如下：
 * img_y:jbyteArray，是摄像头数据的Y指针，该内存大小应该是初始化的j_in_width * j_in_height * j_in_channel
 *       这个需要调用者自己维护和保证
 */
extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_hellolibs_MainActivity_reference(JNIEnv *env, jobject thiz, jbyteArray img_y)
{
    LOGI("reference is called by java");
    return 0;
}

/*
 * 释放资源
 */
extern "C" JNIEXPORT jlong JNICALL
Java_com_example_hellolibs_MainActivity_uninit(JNIEnv *env, jobject thiz)
{
    LOGI("uninit is called by java");
    return 0;
}