#pragma once

#include "atlas.h"
#include <string>
#include <graphics.h>
#include <unordered_map>

class ResourcesManager
{
public:
	static ResourcesManager* GetInstance();
	void load();
	Atlas* getAtlas(const std::string& id)const;
	IMAGE* getImage(const std::string& id)const;

private:
	ResourcesManager();
	~ResourcesManager();

	static ResourcesManager* manager;
	std::unordered_map<std::string, Atlas*> atlasMap;
	std::unordered_map<std::string, IMAGE*> imageMap;

	void flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h = 1);
	void flip_image(const std::string& src_id, const std::string& dst_id, int num_h = 1);
	void flip_atlas(const std::string& src_id, const std::string& dst_id);
};