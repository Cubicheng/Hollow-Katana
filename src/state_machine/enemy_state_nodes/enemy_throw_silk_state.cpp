#include "enemy_throw_silk_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"
#include "../../characters/player.h"

EnemyThrowSilkState::EnemyThrowSilkState(){
	timer.set_one_shot(true);
	timer.set_wait_time(0.9f);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->set_enable_gravity(true);
		enemy->set_throw_silk(false);
		if (!enemy->is_on_floor() && enemy->get_hp() > 5 && ut::range_random(0, 100) <= 25) {
			enemy->switch_state("aim");
		}
		else if (!enemy->is_on_floor()) {
			enemy->switch_state("fall");
		}
		else {
			enemy->switch_state("idle");
		}
		});
}

void EnemyThrowSilkState::on_enter(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_animation("throw_silk");
	enemy->set_enable_gravity(false);
	enemy->set_throw_silk(true);
	enemy->on_throw_silk();
	timer.restart();

	ut::play_audio(_T("enemy_throw_silk"), false);
}

void EnemyThrowSilkState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
}


