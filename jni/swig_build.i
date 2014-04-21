%module AS_Native_Player
%include "std_string.i"
using namespace std;
typedef std::string String;
%{
#include "ASPlayer.h"
#include <stdio.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
%}

%include "ASPlayer.h"