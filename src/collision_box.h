#pragma once

#include "vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
	friend class CollisionManager;
	
private:
	CollisionBox() = default;
	~CollisionBox() = default;

	Vector2 size;
	Vector2 position;
	bool enabled = true;
	std::function<void()> onCollision;
	CollisionLayer layer_src = CollisionLayer::None;//this collision box's layer
	CollisionLayer layer_dst = CollisionLayer::None;//the collision box's layer that is the destination

public:

	void set_enabled(bool enabled) {
		this->enabled = enabled;
	}

	void set_layer_src(CollisionLayer layer) {
		layer_src = layer;
	}

	void set_layer_dst(CollisionLayer layer) {
		layer_dst = layer;
	}

	void set_on_collision(std::function<void()> onCollision) {
		this->onCollision = onCollision;
	}

	void set_size(const Vector2 &size) {
		this->size = size;
	}

	void set_position(const Vector2 &position) {
		this->position = position;
	}

	const Vector2& get_size() const {
		return size;
	}
};