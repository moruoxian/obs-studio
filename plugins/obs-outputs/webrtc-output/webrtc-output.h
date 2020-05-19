#ifndef  _WEBRTC_OUTPUT_H_
#define  _WEBRTC_OUTPUT_H_

#include "obs.h"
#include "obs-module.h"

#ifdef _MSC_VER

#  ifdef WEBRTCSTREAM_EXPORTS
#    define WEBRTCSTREAM_API __declspec(dllexport)
#  else
#    define WEBRTCSTREAM_API __declspec(dllimport)
#  endif
#else
#  ifndef  __APPLE__
#    define WEBRTCSTREAM_API
#  else
#    define WEBRTCSTREAM_API __attribute__((visibility("default")))
#  endif
#endif


WEBRTCSTREAM_API  struct obs_output_info *CreateWebrtcOutput(void (*callback)(void*));
#endif // _WEBRTC_OUTPUT_H_
