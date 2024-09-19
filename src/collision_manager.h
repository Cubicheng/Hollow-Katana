#pragma once

#include "collision_box.h"
#include <vector>

class CollisionManager
{
public:
	static CollisionManager* getInstance();
	CollisionBox* create_collision_box();
	void destroy_collision_box(CollisionBox* collision_box);

	void process_collisions();
	void on_debug_render();

private:
	CollisionManager() = default;
	~CollisionManager() = default;

	std::vector<CollisionBox*> collision_box_list;

	static CollisionManager* manager;

private:
};