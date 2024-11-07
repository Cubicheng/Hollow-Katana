#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyFallState : public StateNode {
public:
	EnemyFallState() = default;
	~EnemyFallState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit()override {}
};