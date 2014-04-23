%module(directors="1") AS_Native_Player
%include "std_string.i"
using namespace std;
typedef std::string String;

%include "carrays.i"
%array_class(unsigned char, ucArray);

%{
#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include "ASPlayer.h"
#include "IVideoDecodeCB.h"
#include "ASVideoDecodeEvent.h"
%}
%feature("director") IVideoDecodeCB;
%feature("director") ASVideoDecodeEvent;
%feature("director") ASPlayer;


%init %{
    JavaVM* g_cached_jvm = NULL;
    JNIEnv* g_cached_env = NULL;
    
    jint JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        g_cached_jvm = vm;
        if (vm->GetEnv((void**)&g_cached_env, JNI_VERSION_1_6) != JNI_OK) {
            return -1;
        }
        return JNI_VERSION_1_6;
    }

    JavaVM* JNI_GetVM()
    {
        return g_cached_jvm;
    }
    
    JNIEnv* JNI_GetEnv()
    {
        return g_cached_env;
    }
%}

%include "ASPlayer.h"
%include "IVideoDecodeCB.h"
%include "ASVideoDecodeEvent.h"
