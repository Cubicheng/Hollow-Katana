#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyDeadState : public StateNode {
public:
	EnemyDeadState() = default;
	~EnemyDeadState() = default;

	void on_enter() override;
	void on_update(float delta) override {}
	void on_exit() override {}

};