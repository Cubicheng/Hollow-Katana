#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyThrowSwordState : public StateNode {
public:
	EnemyThrowSwordState();
	~EnemyThrowSwordState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit()override {}

private:
	Timer timer_throw;
	Timer timer_switch;
};