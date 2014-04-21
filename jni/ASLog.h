/*
 * ASLog.h
 *
 *  Created on: 2014-4-13
 *      Author: atomshuai
 */

#ifndef ASLOG_H_
#define ASLOG_H_
#define APP_NATIVE_TAG "ASPlayer"
#define LOG_INFO "LOG_INFO"
#define LOG_WARN "WARN_INFO"
#define LOG_ERROR "ERROR_INFO"

#ifdef __ANDROID__
#include <android/log.h>

    #define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, APP_NATIVE_TAG, __VA_ARGS__))
    #define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, APP_NATIVE_TAG, __VA_ARGS__))
    #define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, APP_NATIVE_TAG, __VA_ARGS__))
#else
    #define LOGI(...) (printf("%s ",LOG_INFO, APP_NATIVE_TAG, __VA_ARGS__))
    #define LOGW(...) (printf("%s ",LOG_WARN, APP_NATIVE_TAG, __VA_ARGS__))
    #define LOGE(...) (printf("%s ",LOG_ERROR, APP_NATIVE_TAG, __VA_ARGS__))
#endif


#endif /* ASLOG_H_ */
