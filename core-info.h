/*
*  2016.7.26
*  
*/

#pragma once

#include <utility> 
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "Define.h"
#include "func.h"

using namespace std;

static void RenderWindow(void *data, uint32_t cx, uint32_t cy);

//������ƵԴ����
enum class VideoSourceType 
{
	None = 0, //��Ϊδ��������
	Window,  //����
	Cam,		//����ͷ
	Image,		//ͼƬԴ
	File		//ý���ļ�
};

//������ƵԴ����
enum class AudioSourceType 
{
	None = 0,
	Speaker,
	Mic
};

//����filter����
enum class FilterSourceType
{
	None = 0,
	NoiseGate
};

//obs��Դ����
enum class SourceType
{
	None = 0,
	Video,
	Audio,
	Filter
};

union SubSourceType
{
	VideoSourceType videoType;
	AudioSourceType audioType;
	FilterSourceType filterType;
};

//Դ��Ϣ,�ֱ���id,name,�Լ�obs_source����
class SourceInfo 
{
private:
	int _id;
	string _name;
	SourceType _type;
	SubSourceType _sub_type;
	SourceContext _obj;

public:
	inline SourceInfo() 
	{
		_id = -1;
		_name = "";
		_type = SourceType::None;
		_obj = nullptr;
	}

	inline SourceInfo(int id, string name, SourceType type, VideoSourceType sub_type, SourceContext obj)
	{
		_id = id;
		_name = name;
		_type = type;
		_sub_type.videoType = sub_type;
		_obj = obj;
	}

	inline SourceInfo(int id, string name, SourceType type, AudioSourceType sub_type, SourceContext obj)
	{
		_id = id;
		_name = name;
		_type = type;
		_sub_type.audioType = sub_type;
		_obj = obj;
	}

	inline SourceInfo(int id, string name, SourceType type, FilterSourceType sub_type, SourceContext obj)
	{
		_id = id;
		_name = name;
		_type = type;
		_sub_type.filterType = sub_type;
		_obj = obj;
	}

	inline bool isVideoSource()
	{
		return _type == SourceType::Video;
	}

	inline bool isAudioSource()
	{
		return _type == SourceType::Audio;
	}

	inline bool isFilterSource()
	{
		return _type == SourceType::Filter;
	}

	inline SourceType type()
	{
		return _type;
	}

	inline SubSourceType subType()
	{
		return _sub_type;
	}

	inline int id()
	{
		return _id;
	}

	inline string name()
	{
		return _name;
	}

	inline SourceContext obj()
	{
		return _obj;
	}
};

//Դ��Ϣ����
class SourceInfoMgr
{
private:
	vector<SourceInfo> vec_source;
	int id_index;
	//ͨ��Դ���ֲ��Ҷ�Ӧid
	map<string, int> map_name2id;  
	//ͨ��hwnd���Ҷ�Ӧ��Display����
	map<HWND, DisplayContext> map_hwnd2display;
	//ͨ��hwnd���Ҷ�Ӧ�Ĵ��ڴ�С
	map<HWND, SIZE> map_hwnd2size;
	

public:
	SourceInfoMgr()
	{
		//���ڱ�ʶԴid,����
		id_index = -1;
	}

	int AddSource(string name, SourceType type, VideoSourceType sub_type, SourceContext obj)
	{
		//�ж�name�Ƿ����ظ�
		if (map_name2id.find(name) != map_name2id.end())
		{
			return -1;
		}

		id_index++;
		SourceInfo temp(id_index, name, type, sub_type,obj);
		vec_source.push_back(temp);
		map_name2id[name] = id_index;

		return id_index;
	}

	int AddSource(string name, SourceType type, AudioSourceType sub_type, SourceContext obj)
	{
		//�ж�name�Ƿ����ظ�
		if (map_name2id.find(name) != map_name2id.end())
		{
			return -1;
		}

		id_index++;
		SourceInfo temp(id_index, name, type, sub_type, obj);
		vec_source.push_back(temp);
		map_name2id[name] = id_index;

		return id_index;
	}

	int AddSource(string name, SourceType type, FilterSourceType sub_type, SourceContext obj)
	{
		//�ж�name�Ƿ����ظ�
		if (map_name2id.find(name) != map_name2id.end())
		{
			return -1;
		}

		id_index++;
		SourceInfo temp(id_index, name, type, sub_type, obj);
		vec_source.push_back(temp);
		map_name2id[name] = id_index;

		return id_index;
	}

	void DelAllSource()
	{
		std::vector<SourceInfo>::iterator iter = vec_source.begin();
		while (iter != vec_source.end())
		{
			if (!iter->isAudioSource())
			{
				obs_source_release(iter->obj());
			}
			map_name2id.erase(iter->name());
			iter = vec_source.erase(iter);
		}

		return;
	}

	bool DelSource(string name)
	{
		std::vector<SourceInfo>::iterator iter = vec_source.begin();
		while (iter != vec_source.end())
		{
			if (iter->name() == name)
			{
				if (!iter->isAudioSource())
				{
					obs_source_release(iter->obj());
				}
				vec_source.erase(iter);
				map_name2id.erase(name);
				return true;
			}
			iter++;
		}

		return false;
	}

	//��id
	bool GetSourceInfo(int id, SourceInfo& info)
	{
		std::vector<SourceInfo>::iterator iter = vec_source.begin();
		while (iter != vec_source.end())
		{
			if (iter->id() == id)
			{
				info = *iter;
				return true;
			}
			iter++;
		}

		return false;
	}

	//������
	bool GetSourceInfo(string name, SourceInfo& info)
	{
		if (map_name2id.find(name) == map_name2id.end())
		{
			return false;
		}

		return GetSourceInfo(map_name2id[name], info);
	}

	//ȡ��Դ������
	SourceContext GetSourceObj(int id)
	{
		SourceInfo info;
		if (!GetSourceInfo(id, info))
			return nullptr;

		return info.obj();
	}

	SourceContext GetSourceObj(string name)
	{
		if (map_name2id.find(name) == map_name2id.end())
		{
			return nullptr;
		}

		return GetSourceObj(map_name2id[name]);
	}

	vector<SourceInfo> GetAllSourceInfo()
	{
		return vec_source;
	}

	int GetSourceCount()
	{
		return vec_source.size();
	}

	vector<SourceInfo> GetSourceInfo(SourceType type, SubSourceType sub_type)
	{
		vector<SourceInfo> vecSrc = GetAllSourceInfo();

		if (type == SourceType::None)
			return vecSrc;

		vector<SourceInfo> vecReturn;

		VideoSourceType video_sub_type = sub_type.videoType;
		AudioSourceType audio_sub_type = sub_type.audioType;

		for (size_t i = 0; i < vecSrc.size(); i++)
		{
			if (type == SourceType::Video)
			{
				if (vecSrc[i].isVideoSource())
				{
					if (video_sub_type == VideoSourceType::None)
					{
						vecReturn.push_back(vecSrc[i]);
					}
					else if (video_sub_type == vecSrc[i].subType().videoType )
					{
						vecReturn.push_back(vecSrc[i]);
					}
				}
			}
			else
			{
				if (vecSrc[i].isAudioSource())
				{
					if (audio_sub_type == AudioSourceType::None)
					{
						vecReturn.push_back(vecSrc[i]);
					}
					else if (audio_sub_type == vecSrc[i].subType().audioType)
					{
						vecReturn.push_back(vecSrc[i]);
					}
				}
			}
		}

		return vecReturn;
	}

	//����Դ��Ӧ����Ⱦ��hwnd
	bool SetDisplay(SourceContext source, DisplayContext display)
	{
		if (source == nullptr || display == nullptr)
			return false;

		obs_display_add_draw_callback(display, RenderWindow, this);
		return true;
	}

	bool SetDisplay(const char * source_name, HWND hwnd)
	{
		SourceInfo info;
		if (!GetSourceInfo(source_name, info))
			return false;

		if (!info.isVideoSource())
			return false;
		
		DisplayContext display = GetDisplay(hwnd);

		if (!display)
			return false;

		//obs_display_add_draw_callback(display, RenderWindow, info.obj());
		return SetDisplay(info.obj(), display);
	}

	//�Ƴ�
	void RemoveDisplay(SourceContext source, DisplayContext display)
	{
		if (source == nullptr || display == nullptr)
			return;

		obs_display_remove_draw_callback(display, RenderWindow, source);
		return;
	}

	DisplayContext GetDisplay(HWND hwnd)
	{
		if (map_hwnd2display.find(hwnd) != map_hwnd2display.end())
		{
			return map_hwnd2display[hwnd];
		}
		else
		{
			//ȡ��wnd��С������
			RECT rect;
			SIZE size;
			::GetClientRect(hwnd, &rect);
			size.cx = rect.right;
			size.cy = rect.bottom;
			map_hwnd2size[hwnd] = size;

			//����hwnd��С
			DisplayContext display = CreateDisplay(hwnd);
			map_hwnd2display[hwnd] = display;
			return display;
		}

		return nullptr;
	}

};


/*
scene manager
*/


//������ƵԪ��,����λ�ô�С����
struct SceneItemPosInfo
{
	int width;
	int height;
	int x;
	int y;
	float x_scale;
	float y_scale;
	//bool removed;
	//bool size_changed;

	SceneItemPosInfo()
	{
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		x_scale = 0.0;
		y_scale = 0.0;
	}
};

//��¼������ƵԴԪ�ص�λ�ô�С��������ɾ�ĵ�
class SceneItemsMgr
{
private:
	SceneContext scene;
	map<SourceContext, SceneItem> map_item;
	map<SceneItem, SceneItemPosInfo> map_item_pos;
public:
	SceneItemsMgr()
	{
		scene = nullptr;
	}

	void SetScene(SceneContext sc)
	{
		scene = sc;
	}

	SceneContext GetCurrentScene()
	{
		return scene;
	}

	void SetItem(SourceContext src, SceneItem value)
	{
		map_item[src] = value;
	}

	bool SetItemPos(SourceContext src, SceneItemPosInfo &posInfo)
	{
		if (map_item.find(src) == map_item.end())
			return false;

		SceneItem item = map_item[src];

		map_item_pos[item] = posInfo;
		
		return true;
	}

	SceneItem GetItem(SourceContext src)
	{
		if (map_item.find(src) == map_item.end())
			return nullptr;

		return map_item[src];
	}

	bool GetItemPos(SourceContext src, SceneItemPosInfo &posInfo)
	{
		if (map_item.find(src) == map_item.end())
			return false;

		SceneItem item = map_item[src];

		if (map_item_pos.find(item) == map_item_pos.end())
			return false;

		posInfo = map_item_pos[item];
		return true;
	}


};


//����ͷ���ԣ��ֱ��ʣ�fps��
struct CamInfo
{
	string cam_name;
	vector<string> vec_resolution;
	vector< vector<string> > vec_vec_fps;
	vector< vector<long long> > vec_vec_frame_interval;
};

//ֱ��״̬���ݣ���֡��,������
/*
struct StreamingStatus
{
	//fps
	uint64_t lastBytesSent = 0;
	uint64_t lastBytesSentTime = 0;

};
*/
/*
���е�״̬��Ϣ����
*/

struct StatusInfo
{
	//��ʼ���Ƿ�ɹ�
	bool bInit = false;
	//init video
	bool bInitVideo = false;
	//init stream
	bool bInitStream = false;
	//preview wnd �Ƿ�Ԥ�����ڹ�������
	bool bPreviewDisplay = false;

	//����Դ����
	SourceInfoMgr source_mgr;

	//���ڹ�����ƵԴ��λ����Ϣ,���ڽ��е���
	SceneItemsMgr scene_source_mgr;
	
	//��Ӧ������ name,id
	std::vector< std::pair<string, string> > vec_window;

	//std::vector<std::string> vec_cam;
	//��Ӧ ����ͷ name,id
	std::vector< std::pair<string,string> > vec_cam;
	struct CamInfo cam_info;
	std::string str_media_file;

	//struct StreamingStatus streaming_status;


	//hwnd
	HWND hwnd_main = NULL;

	//size
	int base_width = 0;
	int base_height = 0;
	int output_width = 0;
	int output_height = 0;


	//func
	void setWindowsName(std::vector< pair<string, string>  > vec)
	{
		vec_window = vec;
	}

	int GetWinNums()
	{
		return vec_window.size();
	}

	const char* GetWinName(int nIndex)
	{
		if (nIndex > GetWinNums())
			return NULL;

		return vec_window[nIndex].first.c_str();
	}


	const char* GetWinID(int nIndex)
	{
		if (nIndex > GetWinNums())
			return NULL;

		return vec_window[nIndex].second.c_str();
	}


	const char* GetWinID(string name)
	{
		for (int i = 0; i < GetWinNums(); i++)
		{
			if (vec_window[i].first == name)
				return vec_window[i].second.c_str();
		}

		return nullptr;
	}


	void SetCamsName(std::vector< std::pair<string, string> > vec)
	{
		vec_cam = vec;
	}


	int GetCamNums()
	{
		return vec_cam.size();
	}

	const char* GetCamName(int nIndex)
	{
		if (nIndex > GetCamNums())
			return NULL;

		return vec_cam[nIndex].first.c_str();
	}

	const char* GetCamID(int nIndex)
	{
		if (nIndex > GetCamNums())
			return NULL;

		return vec_cam[nIndex].second.c_str();
	}


	const char* GetCamID(string name)
	{
		for (int i = 0; i < GetCamNums(); i++)
		{
			if (vec_cam[i].first == name )
				return vec_cam[i].second.c_str();
		}

		return nullptr;
	}

	// func for source
	SourceContext GetSourceObj(string name)
	{
		return source_mgr.GetSourceObj(name);
	}

	int AddSource(string name, SourceType type, VideoSourceType sub_type, SourceContext obj)
	{
		return  source_mgr.AddSource(name, type, sub_type, obj);
	}

	bool DelSource(string name)
	{
		return source_mgr.DelSource(name);
	}

	vector<SourceInfo> GetAllSourceInfo()
	{
		return source_mgr.GetAllSourceInfo();
	}

	vector<SourceInfo> GetVideoSourceInfo(VideoSourceType type = VideoSourceType::None)
	{
		SubSourceType sub_type;
		sub_type.videoType = type;
		return source_mgr.GetSourceInfo(SourceType::Video, sub_type);
	}

	vector<SourceInfo> GetAudioSourceInfo(AudioSourceType type = AudioSourceType::None)
	{
		SubSourceType sub_type;
		sub_type.audioType = type;
		return source_mgr.GetSourceInfo(SourceType::Audio, sub_type);
	}

	vector<SourceInfo> GetFilterSourceInfo(FilterSourceType type = FilterSourceType::None)
	{
		SubSourceType sub_type;
		sub_type.filterType = type;
		return source_mgr.GetSourceInfo(SourceType::Filter, sub_type);
	}

	vector<SourceContext> GetVideoSourceContext(VideoSourceType type = VideoSourceType::None)
	{
		vector<SourceInfo> vecInfo;
		vector<SourceContext> vecContext;

		vecInfo = GetVideoSourceInfo(type);

		for (size_t i = 0; i < vecInfo.size(); i++)
		{
			vecContext.push_back(vecInfo[i].obj());
		}

		return vecContext;
	}

	vector<SourceContext> GetAudioSourceContext(AudioSourceType type = AudioSourceType::None)
	{
		vector<SourceInfo> vecInfo;
		vector<SourceContext> vecContext;

		vecInfo = GetAudioSourceInfo(type);

		for (size_t i = 0; i < vecInfo.size(); i++)
		{
			vecContext.push_back(vecInfo[i].obj());
		}

		return vecContext;
	}

	vector<SourceContext> GetFilterSourceContext(FilterSourceType type = FilterSourceType::None)
	{
		vector<SourceInfo> vecInfo;
		vector<SourceContext> vecContext;

		vecInfo = GetFilterSourceInfo(type);

		for (size_t i = 0; i < vecInfo.size(); i++)
		{
			vecContext.push_back(vecInfo[i].obj());
		}

		return vecContext;
	}

	//func for scene
	SceneContext GetCurrentScene()
	{
		return scene_source_mgr.GetCurrentScene();
	}

};



static void RenderWindow(void *data, uint32_t cx, uint32_t cy)
{
	obs_video_info ovi;
	obs_get_video_info(&ovi);

	//preview_wnd_width = int(preview_wnd_scale * float(ovi.base_width));
	//preview_wnd_height = int(preview_wnd_scale * float(ovi.base_height));

	gs_viewport_push();
	gs_projection_push();

	/* --------------------------------------- */

	gs_ortho(0.0f, float(ovi.base_width), 0.0f, float(ovi.base_height),
		-100.0f, 100.0f);

	gs_set_viewport(preview_wnd_x, preview_wnd_y,
		preview_wnd_width, preview_wnd_height);

	//obs_source_video_render(src);
	obs_render_main_view();

	gs_load_vertexbuffer(nullptr);

	/* --------------------------------------- */

	float right = float(preview_wnd_width) + preview_wnd_x;
	float bottom = float(preview_wnd_height) + preview_wnd_y;

	gs_ortho(-preview_wnd_x, right,
		-preview_wnd_y, bottom,
		-100.0f, 100.0f);
	gs_reset_viewport();

	struct StatusInfo * ps = (struct StatusInfo *) data;
	SceneContext scene = ps->GetCurrentScene();

	DrawSceneEditing(scene);

	/* --------------------------------------- */

	gs_projection_pop();
	gs_viewport_pop();


}