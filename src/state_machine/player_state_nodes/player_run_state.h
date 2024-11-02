#pragma once

#include "../state_node.h"

class PlayerRunState : public StateNode {
public:
	PlayerRunState() {};
	~PlayerRunState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;
};