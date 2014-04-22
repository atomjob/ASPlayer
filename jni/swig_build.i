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

%include "ASPlayer.h"
%include "IVideoDecodeCB.h"
%include "ASVideoDecodeEvent.h"
