/*
*  2016.7.26
*  mail:purpledaisy@163.com
*/

#pragma once

#include <vector>
#include <map>
#include <string>
#include "Define.h"

using namespace std;

enum class VideoSourceType 
{
	Window = 0,  //����
	Cam		//����ͷ
};

enum class AudioSourceType 
{
	Speaker = 0,
	Mic
};

enum class SourceType
{
	None = 0,
	Video,
	Audio
};

//Դ��Ϣ,�ֱ���id,name,�Լ�obs_source����
class SourceInfo 
{
private:
	int _id;
	string _name;
	SourceType _type;
	SourceContext _obj;
public:
	inline SourceInfo() 
	{
		_id = -1;
		_name = "";
		_type = SourceType::None;
		_obj = nullptr;
	}

	inline SourceInfo(int id, string name, SourceType type, SourceContext obj)
	{
		_id = id;
		_name = name;
		_type = type;
		_obj = obj;
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

public:
	SourceInfoMgr()
	{
		//���ڱ�ʶԴid,����
		id_index = -1;
	}

	int AddSource(string name, SourceType type, SourceContext obj)
	{
		id_index++;
		SourceInfo temp(id_index, name, type, obj);
		vec_source.push_back(temp);
		return id_index;
	}

	bool DelSource(string name, SourceType type)
	{
		std::vector<SourceInfo>::iterator iter = vec_source.begin();
		while (iter != vec_source.end())
		{
			if (iter->name() == name)
			{
				vec_source.erase(iter);
				return true;
			}
			iter++;
		}

		return false;
	}

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

	SourceContext GetSourceObj(int id)
	{
		SourceInfo info;
		if (!GetSourceInfo(id, info))
			return nullptr;

		return info.obj();
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
	map<SourceContext, SceneItem> map_item;
	map<SceneItem, SceneItemPosInfo> map_item_pos;
public:
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