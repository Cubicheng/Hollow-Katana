#pragma once

#include "../state_node.h"

class PlayerIdleState : public StateNode {
public:
	PlayerIdleState() = default;
	~PlayerIdleState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override {}
};