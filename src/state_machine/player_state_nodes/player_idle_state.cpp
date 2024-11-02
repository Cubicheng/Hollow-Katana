#include "player_idle_state.h"
#include "../../characters/character_manager.h"

void PlayerIdleState::on_enter() {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->set_animation("idle");
}

void PlayerIdleState::on_update(float delta) {
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	if (player->get_hp() <= 0)
		player->switch_state("dead");
	else if (player->can_attack())
		player->switch_state("attack");
	else if (player->get_velocity().y > 0)
		player->switch_state("fall");
	else if (player->can_jump())
		player->switch_state("jump");
	else if (player->can_roll())
		player->switch_state("roll");
	else if (player->is_on_floor() && player->get_move_dir() != 0)
		player->switch_state("run");
}