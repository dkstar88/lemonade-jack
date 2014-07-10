LOCAL_PATH := $(call my-dir)
LOCAL_CFLAGS := -w -O2
include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

# LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/AppDelegate.cpp \
#                    ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_store_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,/Users/william/cocos2d/teaegg/cocos2d/cocos)
$(call import-add-path,/Users/william/cocos2d/teaegg/cocos2d/external)
$(call import-add-path,/Users/william/cocos2d/teaegg/cocos2d)
$(call import-add-path,/Users/william/cocos2d/teaegg/cocos2d/cocos/editor-support)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,ui)
# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
$(call import-module, extensions/cocos2dx-store/android/jni)