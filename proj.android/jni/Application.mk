APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCOCOS2D_DEBUG=1 -std=c++11 -fsigned-char
APP_ABI := armeabi
APP_OPTIM := debug
NDK_APP_OPTIM := debug
NDK_DEBUG := 1
APP_PLATFORM := android-14