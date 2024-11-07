#include "enemy_dash_on_floor_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

EnemyDashOnFloorState::EnemyDashOnFloorState(){
	timer.set_one_shot(true);
	timer.set_wait_time(0.5f);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->set_dashing_on_floor(false);
		});
}

void EnemyDashOnFloorState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("dash_on_floor");
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_velocity({ enemy->get_facing_left() ? -SPEED_DASH : SPEED_DASH,0 });
	enemy->set_dashing_on_floor(true);
	enemy->on_dash();
	timer.restart();

	ut::play_audio(_T("enemy_dash"), false);
}

void EnemyDashOnFloorState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("die");
	}
	else if (!enemy->get_dashing_on_floor()) {
		enemy->switch_state("idle");
	}
}


