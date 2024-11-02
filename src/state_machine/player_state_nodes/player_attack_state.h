#pragma once
#include "../state_node.h"
#include "../../timer.h"

class PlayerAttackState : public StateNode {
public:
	PlayerAttackState();
	~PlayerAttackState() = default;

	void on_enter() override;
	void on_update(float delta) override;
	void on_exit() override;

private:
	Timer timer;
private:
	void update_hit_box_position();
};