#pragma once

#include "../state_node.h"

class PlayerFallState : public StateNode {
public:
	PlayerFallState() {}
	~PlayerFallState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override {}
};