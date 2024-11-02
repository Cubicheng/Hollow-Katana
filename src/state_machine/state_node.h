#pragma once

class StateNode {
public:
	StateNode() = default;
	~StateNode() = default;

	virtual void on_enter() = 0;
	virtual void on_update(float delta) = 0;
	virtual void on_exit() = 0;
};