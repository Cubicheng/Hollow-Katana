#pragma once


#include "state_node.h"
#include <string>
#include <unordered_map>

class StateMachine
{
public:
	StateMachine() = default;
	~StateMachine() = default;

	void on_update(float delta);

	void set_entry(const std::string& id);
	void switch_to(const std::string& id);
	void register_state(const std::string& id, StateNode* state_node);

private:
	bool need_init = true;//if true, the first state will be set as entry
	StateNode* current_state = nullptr;
	std::unordered_map<std::string, StateNode*> state_pool;
};