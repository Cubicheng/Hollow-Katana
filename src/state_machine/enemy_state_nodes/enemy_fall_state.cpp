#include "enemy_fall_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

void EnemyFallState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("fall");
}

void EnemyFallState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	
	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
	else if (enemy->is_on_floor()) {
		enemy->switch_state("idle");
	}
}


