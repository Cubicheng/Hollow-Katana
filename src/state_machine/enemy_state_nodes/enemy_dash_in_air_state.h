#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyDashInAirState : public StateNode {
public:
	EnemyDashInAirState();
	~EnemyDashInAirState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	const float SPEED_DASH = 1500.0f;
};