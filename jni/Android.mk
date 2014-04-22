LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ASPlayer
#LOCAL_SRC_FILES := ASPlayer.cpp 
LOCAL_SRC_FILES := $(wildcard $(LOCAL_PATH)/*.cpp | *.cxx) 
				   
LOCAL_C_INCLUDES := ./ffmpeg/include

LOCAL_SHARED_LIBRARIES := 	libavformat \
							libavcodec \
							libswscale \
							libwsresample \
							libavutil \
							libavdevice \
							libavfilter
							

LOCAL_CFLAGS :=  -D__STDC_CONSTANT_MACROS
LOCAL_LDLIBS += -llog -ljnigraphics -lz

# Enable RTTI
LOCAL_CPP_FEATURES += rtti

include $(BUILD_SHARED_LIBRARY)
$(call import-module, arm)