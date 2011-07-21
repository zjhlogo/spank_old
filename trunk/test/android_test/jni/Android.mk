# Build Share lib

MY_LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/../../../build/android/jni/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(CLEAR_VARS)

LOCAL_MODULE:= android_test

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include

LOCAL_SRC_FILES := \
		Main.cpp \
		GameApp.cpp \

LOCAL_LDLIBS := -lz -lm -llog -lGLESv2

LOCAL_STATIC_LIBRARIES := libspank

#LOCAL_SHARED_LIBRARIES :=

include $(BUILD_SHARED_LIBRARY)
