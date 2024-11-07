#include "enemy_dash_in_air_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

EnemyDashInAirState::EnemyDashInAirState()
{
}

void EnemyDashInAirState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("dash_in_air");

	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	const Character* player = CharacterManager::GetInstance()->GetPlayer();
	Vector2 player_pos = { player->get_position().x, (float)player->get_floor_y() };
	enemy->set_velocity((player_pos - enemy->get_position()).normalize() * SPEED_DASH);
	enemy->set_enable_gravity(false);
	enemy->set_dashing_in_air(false);
	enemy->on_dash();

	//ut::play_audio(_T("enemy_dash"), false);
}

void EnemyDashInAirState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	
	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
	else if (enemy->is_on_floor()) {
		enemy->switch_state("idle");
	}
}

void EnemyDashInAirState::on_exit(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_enable_gravity(true);
	enemy->set_dashing_in_air(false);
}
