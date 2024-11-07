#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyJumpState : public StateNode {
public:
	EnemyJumpState() = default;
	~EnemyJumpState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit()override {}

private:
	const float SPEED_JUMP = 1000.0f;
};