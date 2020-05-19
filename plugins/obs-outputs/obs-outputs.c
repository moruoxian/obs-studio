#include <obs-module.h>

#include "obs-outputs-config.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include "webrtc-output/webrtc-output.h" //add by wangjun420200518
#endif

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-outputs", "en-US")
MODULE_EXPORT const char *obs_module_description(void)
{
	return "OBS core RTMP/FLV/null/FTL outputs";
}

extern struct obs_output_info rtmp_output_info;
extern struct obs_output_info null_output_info;
extern struct obs_output_info flv_output_info;
#if COMPILE_FTL
extern struct obs_output_info ftl_output_info;
#endif
//add by wangjun420200518
void callback(void *data)
{
	char *response = (char *)data;
}
//end
bool obs_module_load(void)
{
#ifdef _WIN32
	WSADATA wsad;
	WSAStartup(MAKEWORD(2, 2), &wsad);
#endif

	obs_register_output(&rtmp_output_info);
	obs_register_output(&null_output_info);
	obs_register_output(&flv_output_info);
#if COMPILE_FTL
	obs_register_output(&ftl_output_info);
#endif

    //add by wangjun4 20200518 test add webrtcstream output begin

#ifdef _WIN32
    //增加下面两句
        struct obs_output_info *webrtc_output_info =
            CreateWebrtcOutput(callback);
        obs_register_output(webrtc_output_info);


#endif

    //end 20200518
	return true;
}

void obs_module_unload(void)
{
#ifdef _WIN32
	WSACleanup();
#endif
}
