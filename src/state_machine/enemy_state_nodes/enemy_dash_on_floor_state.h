#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyDashOnFloorState : public StateNode {
public:
	EnemyDashOnFloorState();
	~EnemyDashOnFloorState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override {}

private:
	Timer timer;
	const float SPEED_DASH = 1000.0f;
};