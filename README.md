1:将snpe-1.68.0.3932/examples/NativeCpp/SampleCode/jni目录中的C代码进行封装和修改，编译成Android的SO
  这个编译方介绍，将在另外一个工程中介绍
2：该工程的主体是将ndk-sample/hello-libs工程作为蓝本，来进行修改。

下面详细介绍下修改内容
3：将1的步骤中生成的头文件SnpeLoader.h以及库libsnpe-action.s0放到distribution/snpe下的include和lib/arm64-v8a(目前设备仅支持arm64的架构)
4：工程中，gmath和gperf是以前工程中带的例子，目前被注释调了，可以不用管它
5：在app/build.gradle中添加“ndk.abiFilters 'arm64-v8a'”，只是生成arm64的架构
6：JNI的地址主要在：app/src/main/cpp下面，重点再介绍这个目录下的内容
    6.1 android_log.h封装的是Android的Jni曾使用的Log输出，整个Jni曾的输出都可以使用该接口输出
    6.2 resize_image.cpp和h文件，是作Y分量的resize算法，目前是支持最简单的resize算法，以后支持双线性差值算法，可以写到里面来
    6.3 snpe_env.cpp和h文件，因为Snpe SDK的DSP环境需要APK设置环境变量，具体请参考：https://developer.qualcomm.com/sites/default/files/docs/snpe/dsp_runtime.html，所以需要在JNI曾调用setenv来设置环境变量
    6.4 hello-libs.cpp是JNI的主体函数，有初始化函数，每个推理的函数，同时还有释放函数。
具体的函数功能和用法，请看每个文件里面的注释。
7：CMakeLists.txt 是将这个文件夹中的文件生成so，并且按照so的依赖需要，将Snpe SDK中的SO也copy到工程里面来。具体的Copy位置在：snpe-1.68/lib/aarch64-android-clange8.0下面
8：介绍app/src/main/java/com/example/hellolibs/MainActivity.java,该文件的Native函数，是调用了JNI的相对应的函数，具体可以查看该文件中的注释
