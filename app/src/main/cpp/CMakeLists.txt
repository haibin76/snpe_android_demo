
#
# Copyright (C) The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

# configure import libs
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution)

#add_library(lib_gmath STATIC IMPORTED)
#set_target_properties(lib_gmath PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/gmath/lib/${ANDROID_ABI}/libgmath.a)

# ${ANDROID_ABI} is handy for our purpose here. Probably this ${ANDROID_ABI} is
# the most valuable thing of this sample, the rest are pretty much normal cmake
#add_library(lib_gperf SHARED IMPORTED)
#set_target_properties(lib_gperf PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/gperf/lib/${ANDROID_ABI}/libgperf.so)

#libaction_snpe.so
#这个SO是我们编译snpe-1.68.0.3932/example/NativeCpp/SampleCode/Jni生成的so
add_library(lib_action_snpe SHARED IMPORTED)
set_target_properties(lib_action_snpe PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libaction_snpe.so)

##################################################################################
#########################dsp folder 5 so set######################################
#下面五个so是snpe-1.68.0.3932/lib/dsp下面的so，目前可能没用，但是全部copy过来
#libcalculator_skel.so
#add_library(lib_calculator_skel SHARED IMPORTED)
#set_target_properties(lib_calculator_skel PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/dsp/libcalculator_skel.so)

#libsnpe_dsp_v65_domains_v2_skel.so
#add_library(lib_snpe_dsp_v65_domains_v2_skel SHARED IMPORTED)
#set_target_properties(lib_snpe_dsp_v65_domains_v2_skel PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/dsp/libsnpe_dsp_v65_domains_v2_skel.so)

#libsnpe_dsp_v66_domains_v2_skel.so
#add_library(lib_snpe_dsp_v66_domains_v2_skel SHARED IMPORTED)
#set_target_properties(lib_snpe_dsp_v66_domains_v2_skel PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/dsp/libsnpe_dsp_v66_domains_v2_skel.so)

#libSnpeHtpV68Skel.so
#add_library(lib_SnpeHtpV68Skel SHARED IMPORTED)
#set_target_properties(lib_SnpeHtpV68Skel PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/dsp/libSnpeHtpV68Skel.so)

#libSnpeHtpV69Skel.so
#add_library(lib_SnpeHtpV69Skel SHARED IMPORTED)
#set_target_properties(lib_SnpeHtpV69Skel PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/dsp/libSnpeHtpV69Skel.so)

##################################################################################
#########################arm64-v8a 10 so set #####################################
#下面10个so是snpe-1.68.0.3932/lib/aarch64-android-clang8.0的so，目没有全部使用
#libc++_shared.so
add_library(lib_c++_shared SHARED IMPORTED)
set_target_properties(lib_c++_shared PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libc++_shared.so)

#libcalculator_htp.so
#add_library(lib_calculator_htp SHARED IMPORTED)
#set_target_properties(lib_calculator_htp PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libcalculator_htp.so)

#libcalculator.so
#add_library(lib_calculator SHARED IMPORTED)
#set_target_properties(lib_calculator PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libcalculator.so)

#libhta.so
#add_library(lib_hta SHARED IMPORTED)
#set_target_properties(lib_hta PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libhta.so)

#libPlatformValidatorShared.so
#add_library(lib_PlatformValidatorShared SHARED IMPORTED)
#set_target_properties(lib_PlatformValidatorShared PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libPlatformValidatorShared.so)

#libsnpe_dsp_domains_v2.so
#add_library(lib_snpe_dsp_domains_v2 SHARED IMPORTED)
#set_target_properties(lib_snpe_dsp_domains_v2 PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libsnpe_dsp_domains_v2.so)

#libSNPE.so
add_library(lib_SNPE SHARED IMPORTED)
set_target_properties(lib_SNPE PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libSNPE.so)

#libSnpeHtpPrepare.so
#add_library(lib_SnpeHtpPrepare SHARED IMPORTED)
#set_target_properties(lib_SnpeHtpPrepare PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libSnpeHtpPrepare.so)

#libSnpeHtpV68Stub.so
#add_library(lib_SnpeHtpV68Stub SHARED IMPORTED)
#set_target_properties(lib_SnpeHtpV68Stub PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libSnpeHtpV68Stub.so)

#libSnpeHtpV69Stub.so
#add_library(lib_SnpeHtpV69Stub SHARED IMPORTED)
#set_target_properties(lib_SnpeHtpV69Stub PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/snpe/lib/${ANDROID_ABI}/lib/libSnpeHtpV69Stub.so)

# build application's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(hello-libs SHARED hello-libs.cpp resize_image.cpp snpe_env.cpp)

target_include_directories(hello-libs PRIVATE
                           #${distribution_DIR}/gmath/include
                           #${distribution_DIR}/gperf/include
                           ${distribution_DIR}/snpe/include
)

target_link_libraries(hello-libs
                        android
#                       lib_gmath
#                       lib_gperf
                        lib_action_snpe

        #               lib_calculator_skel
        #               lib_snpe_dsp_v65_domains_v2_skel
        #               lib_snpe_dsp_v66_domains_v2_skel
        #                lib_SnpeHtpV68Skel
        #                lib_SnpeHtpV69Skel

                        lib_c++_shared
        #               lib_calculator_htp
        #               lib_calculator
        #               lib_hta
        #               lib_PlatformValidatorShared
        #               lib_snpe_dsp_domains_v2
                       lib_SNPE
        #               lib_SnpeHtpPrepare
        #               lib_SnpeHtpV68Stub
        #               lib_SnpeHtpV69Stub
                        log)

#add_library(snpe-env SHARED snpe_env.cpp)

#target_include_directories(snpe-env PRIVATE
#        ${distribution_DIR}/gperf/include
#        ${distribution_DIR}/snpe/include
#)

#target_link_libraries(snpe-env
#        android
#        log)