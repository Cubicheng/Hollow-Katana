#include "enemy_idle_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

EnemyIdleState::EnemyIdleState(){
	timer.set_one_shot(true);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		
		int rand_num = ut::range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 25) {
				if (!enemy->is_on_floor())
					enemy->switch_state("fall");
				else 
					enemy->switch_state("jump"); //25%
			}
			else if (rand_num <= 50) {
				if (!enemy->is_on_floor())
					enemy->switch_state("fall");
				else
					enemy->switch_state("run"); //25%
			}
			else if (rand_num <= 80) {
				enemy->switch_state("squat"); //30%
			}
			else if (rand_num <= 90) {
				enemy->switch_state("throw_silk");//10%
			}
			else {
				enemy->switch_state("throw_sword");//10%
			}
		}
		else {
			if (rand_num <= 25) {
				if (!enemy->is_on_floor())
					enemy->switch_state("fall");
				else
					enemy->switch_state("jump"); //25%
			}
			else if (rand_num <= 60) {
				enemy->switch_state("throw_sword");//35%
			}
			else if (rand_num <= 70) {
				enemy->switch_state("throw_silk");//10%;
			}
			else if (rand_num <= 90) {
				enemy->switch_state("throw_barb");//20%
			}
			else {
				enemy->switch_state("squat"); //10%
			}
		}
		});
}

void EnemyIdleState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("idle");

	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_velocity({ 0,0 });

	float wait_time = 0;
	if (enemy->get_hp() > 5) {
		wait_time = ut::range_random(0, 2) * 0.25f;
	}
	else {
		wait_time = ut::range_random(0, 1) * 0.25f;
	}

	timer.set_wait_time(wait_time);
	timer.restart();
}

void EnemyIdleState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
	else if (enemy->get_velocity().y > 0) {
		enemy->switch_state("fall");
	}
}

void EnemyIdleState::on_exit(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	Player * player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	enemy->set_facing_left(enemy->get_position().x > player->get_position().x);
}
