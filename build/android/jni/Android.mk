# Build Static lib

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libspank

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include

LOCAL_SRC_FILES := \
		FileMgr_Impl.cpp \
		DebugUtil_Impl.cpp \
		Renderer_Impl.cpp \
		unzip/unzip.cpp \
		unzip/ioapi.cpp \
		../../../source/IGameMain.cpp \
		../../../source/util/StreamReader.cpp \
		../../../source/util/StreamWriter.cpp \

#LOCAL_LDLIBS :=

#LOCAL_STATIC_LIBRARIES :=

#LOCAL_SHARED_LIBRARIES :=

include $(BUILD_STATIC_LIBRARY)
