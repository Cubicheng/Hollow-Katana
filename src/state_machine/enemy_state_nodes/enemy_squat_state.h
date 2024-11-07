#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemySquatState : public StateNode {
public:
	EnemySquatState();
	~EnemySquatState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit()override {}
private:
	Timer timer;
};