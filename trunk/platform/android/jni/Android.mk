# Copyright (C) 2009 The Android Open Source Project
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
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := spank

LOCAL_SRC_FILES := \
		FileMgr_Impl.cpp \
		DebugUtil_Impl.cpp \
		Main.cpp \
		Renderer_Impl.cpp \
		GameMain_Impl.cpp \
		unzip/unzip.cpp \
		unzip/ioapi.cpp \
		../../../source/IGameMain.cpp \
		../../../source/MessageHandler.cpp \
		../../../source/MessageMgr.cpp \
		../../../source/msg/MsgBase.cpp \
		../../../source/msg/MsgReader.cpp \
		../../../source/msg/MsgWriter.cpp \
		../../../source/msg/MsgDummy.cpp \
		../../../source/util/StreamReader.cpp \
		../../../source/util/StreamWriter.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include

LOCAL_LDLIBS    := -llog -lz -lGLESv2

subdirs := $(LOCAL_PATH)/../../../source/Android.mk

include $(BUILD_SHARED_LIBRARY)

