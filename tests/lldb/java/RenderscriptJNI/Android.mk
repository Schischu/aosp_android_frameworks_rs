LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call all-java-files-under, src) \
                   $(call all-renderscript-files-under, src)

LOCAL_PACKAGE_NAME := RenderscriptJNI

LOCAL_SDK_VERSION := 21

LOCAL_JNI_SHARED_LIBRARIES := renderscriptjni

LOCAL_RENDERSCRIPT_FLAGS := -g -O0

include $(BUILD_PACKAGE)
include $(LOCAL_PATH)/renderscriptjni/Android.mk

