# define source files
LIBPNG_SOURCE := ../../../vendor/lpng154
LIBTINYXML_SOURCE := ../../../vendor/tinyxml-2.6.2
LIBSPANK_SOURCE := ../../../source
LIBGAME_SOURCE := ../../source
LIBANDROID_SOURCE := ./

# build share librarys android_test
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := android_test

# libpng sources
include $(LOCAL_PATH)/$(LIBPNG_SOURCE)/source.mk

# libtinyxml sources
include $(LOCAL_PATH)/$(LIBTINYXML_SOURCE)/source.mk

# libspank sources
include $(LOCAL_PATH)/$(LIBSPANK_SOURCE)/source.mk

# game sources
include $(LOCAL_PATH)/$(LIBGAME_SOURCE)/source.mk

# android sources
include $(LOCAL_PATH)/$(LIBANDROID_SOURCE)/source.mk

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include $(LOCAL_PATH)/../../../vendor
LOCAL_SRC_FILES := \
		$(LIBPNG_SOURCE_FILES) \
		$(LIBTINYXML_SOURCE_FILES) \
		$(LIBSPANK_SOURCE_FILES) \
		$(LIBGAME_SOURCE_FILES) \
		$(LIBANDROID_SOURCE_FILES) \

LOCAL_LDLIBS := -lz -lm -llog -lGLESv2
# LOCAL_STATIC_LIBRARIES := 
# LOCAL_SHARED_LIBRARIES :=
include $(BUILD_SHARED_LIBRARY)
