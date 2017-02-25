/*
2016/10/11
����libobs�ķ�װ
�ṩ�����õĽӿں���
core_xx ���Ƕ���Ľӿں���
������Ϊ�ڲ�ʹ�õĺ���

2016/11/1
������������libcore-internal.h

*/

#pragma once

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include "Define.h"

/**
* init & uninit
* ��ʼ��/����ʼ��
*/
extern "C" LIBCORE_API bool core_init(  const char *module_bin_path = nullptr,
										const char *module_data_path = nullptr,
										const char *module_config_path = nullptr);

extern "C" LIBCORE_API void core_uninit();


/**
* scene
* ������������ص�Դ ��غ���
*/

/** ��ʼ������ */
extern "C" LIBCORE_API bool core_create_scene(const char * scene_name);

/** ���Դ�������� */
extern "C" LIBCORE_API bool core_scene_add_source(const char * scene_name, const char * source_name, bool visible = true);

/** ����Դ�ڳ�������ʾʱ�������� */
extern "C" LIBCORE_API void core_set_source_scale(const char * source_name, float x_scale, float y_scale);

/** ����Դ�ڳ�������ʾ�Ĵ�С */
extern "C" LIBCORE_API void core_set_source_size(const char * source_name, int width, int height);

/** ����Դ�ڳ����е���ʾλ�� */
extern "C" LIBCORE_API void core_set_source_pos(const char * source_name, int x, int y);

/** Դ�ڳ����� z��λ��up or down */
extern "C" LIBCORE_API void core_set_source_order(const char * source_name, int z_position);

/** Դ�Ƿ�ɼ� */
extern "C" LIBCORE_API bool core_set_source_visible( const char * source_name, bool visible);

/** ��ƵԴ��λ�ü�������Ϣ */
extern "C" LIBCORE_API bool core_get_source_pos_info(const char * source_name, int* x, int* y, float* x_scale, float* y_scale);

/** ��ƵԴ��λ�ü���С */
extern "C" LIBCORE_API bool core_get_source_region(const char * source_name, int* x, int* y, float* width, float* height);

/** �Ƴ����� todo */
extern "C" LIBCORE_API bool core_scene_remove(const char * source_name);

/** �л����� todo */
extern "C" LIBCORE_API bool core_scene_switch_to(const char * source_name);


/**
*audio
*��Ƶ��ش�����
*/
/** ��Ƶ��ʼ������ */
extern "C" LIBCORE_API bool core_set_audio(int samples_per_sec = 44100, int bit = 32);

/** ��Ƶ�豸���أ�ֻ����Ĭ�ϵ���������豸 */
extern "C" LIBCORE_API void core_load_audio();

/** ��������Ƿ��� */
extern "C" LIBCORE_API void core_set_audio_output_mute(bool mute);

/** ��������������� range 0.0 - 1.0 */
extern "C" LIBCORE_API void core_set_audio_output_volume(float volume);

/** ���������Ƿ��� */
extern "C" LIBCORE_API void core_set_audio_input_mute(bool mute);

/** ���������������� range 0.0 - 1.0 */
extern "C" LIBCORE_API void core_set_audio_input_volume(float volume);

/** ָ����ǰ�����豸 todo*/
extern "C" LIBCORE_API void core_set_audio_input_device(const char* device_name);

/** ָ����ǰ����豸 todo*/
extern "C" LIBCORE_API void core_set_audio_output_device(const char* device_name);

/** ��ǰ���õ���Ƶ�����豸���� todo */
extern "C" LIBCORE_API int core_get_audio_input_device_num();

/** ȡ��ָ����Ŷ�Ӧ�������豸���� todo */
extern "C" LIBCORE_API const char* core_get_audio_input_device_name(size_t index);

/** ��ǰ���õ���Ƶ����豸���� todo */
extern "C" LIBCORE_API int core_get_audio_output_device_num();

/** ȡ��ָ����Ŷ�Ӧ������豸���� todo */
extern "C" LIBCORE_API const char* core_get_audio_output_device_name(size_t index);



/**
* video
*/

/** ������Ƶ��Ԥ����С�������С */
extern "C" LIBCORE_API int core_set_video(HWND hwnd, int base_width, int base_height, int output_width, int output_height, int fps = 30);

/** ����Ԥ�������Ƿ���ʾ */
extern "C" LIBCORE_API bool core_set_preview_display(bool enabled = true);

//Դ���Ƴ�
extern "C" LIBCORE_API bool core_source_remove(const char * source_name);

/** ȡ����ƵԪ�ص�ʵ�ʴ�С��Ϣ */
extern "C" LIBCORE_API bool core_get_source_base_size(const char * source_name, int* width, int* height);

/** ȡ����Ⱦ����Ĵ�С renderWindow�У�ʵ��ʹ�õ�����*/
//x,y ���Ͻ�����
//width,height,���߶�
extern "C" LIBCORE_API bool core_get_preview_render_region(int *x, int *y, int* width, int* height);

/** ������Ƶ�ļ�������� */
//output_width, output_height�����С
//fps ֡��
//rate ����
//encoder_type �������:1��� 2Ӳ��
extern "C" LIBCORE_API int core_reset_video(int output_width, int output_height, int fps, int rate, int encoder_type);

/**
* window source
*/

/** ����������Դ */
extern "C" LIBCORE_API bool core_create_win_capture_source(const char * source_name);

/** ȡ�ÿ��ô������� */
extern "C" LIBCORE_API int core_get_win_num();

/** ȡ��ָ��������Ŷ�Ӧ�Ĵ������� */
extern "C" LIBCORE_API const char* core_get_win_name(size_t index);

/** ��������Դ���䴰�� */
extern "C" LIBCORE_API bool core_set_win_capture_source(const char * win_name, const char * source_name);



/*
cam source
*/

/** ��������ͷԴ */
extern "C" LIBCORE_API bool core_create_cam_source(const char * source_name);

/** ȡ�ÿ�������ͷ���� */
extern "C" LIBCORE_API int core_get_cam_num();

/** ȡ��ָ����Ŷ�Ӧ������ͷ���� */
extern "C" LIBCORE_API const char* core_get_cam_name(size_t index);

/** ��������ͷԴ��������ͷ */
extern "C" LIBCORE_API bool core_set_cam_source(const char * cam_name, const char * source_name);

/** ��������ͷ����*/
extern "C" LIBCORE_API bool core_set_cam_format(const char * source_name, const char * cam_name, const char * resolution, int fps);

/** ȡ��ǰ����ͷ����*/
extern "C" LIBCORE_API bool core_get_cam_format(const char * source_name, const char * cam_name, int index, char * resolution, char * fps_list);

/** ȡ����ͷ֧�ֱַ�������*/
extern "C" LIBCORE_API int core_get_cam_format_num(const char * source_name, const char * cam_name);

/** ȡ����ͷ֧�ֱַ��� todo*/
//extern "C" LIBCORE_API bool core_get_cam_specific_format(const char * cam_name, int index, char * //resolution, int * fps);

/**
* media source
* ��ý��Դ������غ���
*/

/** ������ý���ļ�Դ */
extern "C" LIBCORE_API bool core_create_file_source(const char * source_name);

/** ������ý���ļ�Դ�����ļ� */
extern "C" LIBCORE_API bool core_set_file_source(const char *filename, const char * source_name);




/**
* rtmp service
* rtmp��ý��������
*/

/** ��ʼ���� */
extern "C" LIBCORE_API  bool core_init_stream();

/** �������Ĳ��� */
extern "C" LIBCORE_API bool core_set_stream_parameters(const char * rtmp_url = "", int videoBitrate = 2500, int audioBitrate = 160);

/** ������������ */
extern "C" LIBCORE_API bool core_start_stream();

/** ֹͣ������ͣ���� */
extern "C" LIBCORE_API void core_stop_stream();

/**����¼�Ʋ��� */
extern "C" LIBCORE_API bool core_set_record_parameters(const char * record_path, const char* format = "flv");

/** ��ʼ¼�� todo */
extern "C" LIBCORE_API bool core_start_record();

/** ֹͣ¼�� todo*/
extern "C" LIBCORE_API void core_stop_record();

/**
* setup
* ϵͳ����
*/

/** ����aeroЧ��*/
extern "C" LIBCORE_API void core_set_aero_on(bool enabled);

/** �����Ƿ���ʾ���*/
extern "C" LIBCORE_API void core_set_mouse_on(bool enabled);

/** �����Ƿ���ʾֱ������ todo */
extern "C" LIBCORE_API void core_set_live_status_on(bool enabled);

/** ����ȫ����Ϸʱ��ʾֱ������ todo */
extern "C" LIBCORE_API void core_set_screen_live_status_on(bool enabled);

/** ������ݼ� todo */
extern "C" LIBCORE_API void core_set_hotkey_on(bool enabled);

/** ����ֱ����ݼ� todo */
extern "C" LIBCORE_API void core_set_hotkey_streaming(const char * hotkey);

/** ����¼�ƿ�ݼ� todo */
extern "C" LIBCORE_API void core_set_hotkey_record(const char * hotkey);

/** ������˷��ݼ� todo */
extern "C" LIBCORE_API void core_set_hotkey_mic(const char * hotkey);

/** �������촰����ʾ��ݼ� todo */
extern "C" LIBCORE_API void core_set_hotkey_chat(const char * hotkey);

/** ��Ƶ���� range 0.0-1.0*/
extern "C" LIBCORE_API bool core_set_audio_denoise(float denoise);

/** ������Ƶ���� todo */
extern "C" LIBCORE_API void core_set_video_output_parameter(const char * resolution, int fps, int bitrage, int encode_type);

/** ����������������� todo */
extern "C" LIBCORE_API void core_set_output_encoder(const char * encoder_name);

/** ȡ��ֱ����ʵʱ����*/
extern "C" LIBCORE_API bool core_get_stream_bitrate(double *rate);

/** ȡ��ֱ����fps*/
extern "C" LIBCORE_API bool core_get_stream_fps(int* fps);

/** ȡ�ö�֡��*/
extern "C" LIBCORE_API bool core_get_stream_dropframes_rate(double *rate);

/** ¼������ todo */
extern "C" LIBCORE_API bool core_set_stream_record_path(const char * record_save_path);



/**
* draw selected item
* ����ʱ����Ԫ�صı߿�
*/

/** ѡ��Ԫ��  editing debuging*/
extern "C" LIBCORE_API bool core_source_select(const char * source_name, bool select = true);