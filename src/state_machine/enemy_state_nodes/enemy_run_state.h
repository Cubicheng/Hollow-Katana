#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyRunState : public StateNode {
public:
	EnemyRunState() = default;
	~EnemyRunState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	const float MIN_DIS = 350.0f;
	const float SPEED_RUN = 500.0f;
};