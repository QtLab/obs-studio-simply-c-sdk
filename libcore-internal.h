/*
2016/11/1
�ڲ�ʹ�ú�������
*/

#pragma once


#include "Define.h"

/*
log
*/
#define do_log(level, format, ...) \
	blog(level, "[libcore : '%s'] " format, \
			"obs interface ", ##__VA_ARGS__)

#define warn(format, ...)  do_log(LOG_WARNING, format, ##__VA_ARGS__)
#define info(format, ...)  do_log(LOG_INFO,    format, ##__VA_ARGS__)
#define debug(format, ...) do_log(LOG_DEBUG,   format, ##__VA_ARGS__)
#define error(format, ...) do_log(LOG_DEBUG,   format, ##__VA_ARGS__)


/*
init & uninit
*/
void clear_scene_data();


/*
modules
*/
void add_modules_path(const char *bin, const char *data);
void load_all_modules();

/*
scene
*/


//���Դ��������
bool scene_add_source(const char * scene_name, SourceContext source, bool visible = true);

//ȡ�ó���Ԫ��λ����Ϣ
void refresh_scene_item_pos(SourceContext src);
void set_scene_item_scale(SourceContext src_ctx, float x_scale, float y_scale);
void set_scene_pos(SourceContext src_ctx, int x, int y);



//����Ԫ��z��λ��up or down
void set_scene_item_order(SceneItem item, enum obs_order_movement movement);
void set_scene_item_order_up(SourceContext src_ctx);
void set_scene_item_order_down(SourceContext src_ctx);


//scene item visible
bool set_scene_item_visible(SceneItem item, bool visible);
bool set_scene_item_visible_by_src(SourceContext src_ctx, bool visible);


/*
source
*/


/*
audio
*/
void get_audio_devices_info();



/*
window source
*/

bool init_windows_info(obs_source_t * src);

//��������Ƿ�׽
void set_window_capture_mouse(obs_source_t * src, bool enable);

/*
cam source
*/

//����ͷ�б�
bool init_cams_info(obs_source_t * src);
//����ͷ�ֱ��ʣ�fps��
bool init_cams_set_info(obs_source_t *src, const char * device_name);

/*
filter source
*/

//��ʼ�� filter source, noise_gate, δ�������
bool init_noise_gate_filter();


/*
rtmp service
*/
bool InitService();
void InitPrimitives();
void SetRtmpURL(const char* rtmp_url);


/*
streaming status
ֱ��״ֵ̬
*/
/*
void stream_started();
void stream_stopped();
*/