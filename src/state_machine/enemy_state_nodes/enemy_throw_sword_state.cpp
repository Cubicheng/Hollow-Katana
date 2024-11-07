#include "enemy_throw_sword_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"
#include "../../characters/player.h"

EnemyThrowSwordState::EnemyThrowSwordState(){
	timer_throw.set_wait_time(0.65f);
	timer_throw.set_one_shot(true);
	timer_throw.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->throw_sword();
		ut::play_audio(_T("enemy_throw_sword"), false);
		});

	timer_switch.set_wait_time(1.0f);
	timer_switch.set_one_shot(true);
	timer_switch.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		int rand_num = ut::range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 50) {
				enemy->switch_state("squat");//50%
			}
			else if (rand_num <= 80) {
				enemy->switch_state("jump");//30%
			}
			else {
				enemy->switch_state("idle");//20%
			}
		}
		else {
			if (rand_num <= 50) {
				enemy->switch_state("jump");//50%
			}
			else if (rand_num <= 80) {
				enemy->switch_state("throw_silk");//30%
			}
			else {
				enemy->switch_state("idle");//20%
			}
		}
		});
}

void EnemyThrowSwordState::on_enter(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_animation("throw_sword");
	timer_throw.restart();
	timer_switch.restart();
}

void EnemyThrowSwordState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();

	timer_throw.on_update(delta);
	timer_switch.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
}


