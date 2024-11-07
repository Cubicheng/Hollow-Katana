#include "enemy_jump_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

void EnemyJumpState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("jump");

	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_velocity({ 0,-SPEED_JUMP });
}

void EnemyJumpState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	
	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
	else if (enemy->get_velocity().y > 0) {//at the falling begining
		int rand_num = ut::range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 50) {
				enemy->switch_state("aim");//50%
			}
			else if (rand_num <= 80) {
				enemy->switch_state("fall");//30%
			}
			else {
				enemy->switch_state("throw_silk");//20%
			}
		}
		else {
			if (rand_num <= 50) {
				enemy->switch_state("throw_silk");//50%
			}
			else if (rand_num <= 80) {
				enemy->switch_state("fall");//30%
			}
			else {
				enemy->switch_state("aim");//20%
			}
		}
	}
}
