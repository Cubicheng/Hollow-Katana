#pragma once
#include "../state_node.h"

class PlayerJumpState : public StateNode {
public:
	PlayerJumpState() = default;
	~PlayerJumpState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override {}
};