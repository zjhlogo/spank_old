# define source files
LIBSPANK_SOURCE := ../../../source
LIBGAME_SOURCE := ../../source
LIBANDROID_SOURCE := ./

# build share librarys android_test
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := android_test

# spank sources
include $(LOCAL_PATH)/$(LIBSPANK_SOURCE)/source.mk

# game sources
include $(LOCAL_PATH)/$(LIBGAME_SOURCE)/source.mk

# android sources
include $(LOCAL_PATH)/$(LIBANDROID_SOURCE)/source.mk

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include
LOCAL_SRC_FILES := $(LIBANDROID_SOURCE_FILES) \
		$(LIBSPANK_SOURCE_FILES) \
		$(LIBGAME_SOURCE_FILES) \

LOCAL_LDLIBS := -lz -lm -llog -lGLESv2
LOCAL_STATIC_LIBRARIES := 
# LOCAL_SHARED_LIBRARIES :=
include $(BUILD_SHARED_LIBRARY)
