#include<obs-module.h>

struct webrtc_stream {
  char *server, *user,*output;
};

static const char *webrtc_stream_name(void *unused)
{
  UNUSED_PARAMETER(unused);
  return obs_module_text("WebRTC Streaming Server");
}

static void webrtc_stream_update(void *data, obs_data_t *settings)
{
  struct webrtc_stream *service = data;

  bfree(service->server); 
  bfree(service->user);
  bfree(service->output);
  service->server   = bstrdup(obs_data_get_string(settings, "server"  )); 
  service->user    = bstrdup(obs_data_get_string(settings, "username"));
  service->output  = bstrdup("webrtc_output");
}

static void webrtc_stream_destroy(void *data)
{
  struct webrtc_stream *service = data;

  bfree(service->server  );  
  bfree(service->user   );
  bfree(service->output);
  bfree(service          );
}

static void *webrtc_stream_create(obs_data_t *settings, obs_service_t *service)
{
  struct webrtc_stream *data = bzalloc(sizeof(struct webrtc_stream));
  webrtc_stream_update(data, settings);

  UNUSED_PARAMETER(service);
  return data;
}

static obs_properties_t *webrtc_stream_properties(void *unused)
{
  UNUSED_PARAMETER(unused);

  obs_properties_t *ppts = obs_properties_create(); 
  obs_properties_add_text(ppts, "server",obs_module_text("Server"), OBS_TEXT_DEFAULT);
  obs_properties_add_text(ppts, "username", obs_module_text("UserName"),OBS_TEXT_DEFAULT); 

  return ppts;
}

static const char *webrtc_stream_url(void *data)
{
  struct webrtc_stream *service = data;
  return service->server;
}


static const char *webrtc_stream_user(void *data)
{
  struct webrtc_stream *service = data;
  return service->user;
}

static const char *webrtc_stream_get_output_type(void *data)
{
	struct webrtc_stream *service = data;
	return service->output;
}

struct obs_service_info webrtc_stream_service = {
  .id              = "webrtc_stream",
  .get_name        = webrtc_stream_name,
  .create          = webrtc_stream_create,
  .destroy         = webrtc_stream_destroy,
  .update          = webrtc_stream_update,
  .get_properties  = webrtc_stream_properties,
  .get_url         = webrtc_stream_url,   
  .get_username    = webrtc_stream_user,
  .get_output_type = webrtc_stream_get_output_type
};
