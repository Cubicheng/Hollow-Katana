#pragma once

#include "../state_node.h"
#include "../../timer.h"

class EnemyAimState : public StateNode {
public:
	EnemyAimState();
	~EnemyAimState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() {}
	
private:
	Timer timer;
};