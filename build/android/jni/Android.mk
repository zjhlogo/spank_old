LOCAL_PATH := $(call my-dir)

# Define vars for library that will be build statically.
include $(CLEAR_VARS)
LOCAL_MODULE := spank
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_SRC_FILES := \
		FileMgr_Impl.cpp \
		DebugUtil_Impl.cpp \
		Main.cpp \
		Renderer_Impl.cpp \
		GameMain_Impl.cpp \
		unzip/unzip.cpp \
		unzip/ioapi.cpp \
		../../../source/IGameMain.cpp \
		../../../source/util/StreamReader.cpp \
		../../../source/util/StreamWriter.cpp \

# Optional compiler flags.
# LOCAL_LDLIBS   = -lz -lm
# LOCAL_CFLAGS   = -Wall -pedantic -std=c99 -g

include $(BUILD_STATIC_LIBRARY)

# First lib, which will be built statically.
include $(CLEAR_VARS)
LOCAL_MODULE := main
LOCAL_STATIC_LIBRARIES := spank

include $(BUILD_SHARED_LIBRARY)
