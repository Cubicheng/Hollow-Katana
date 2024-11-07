#include "enemy_aim_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"

EnemyAimState::EnemyAimState(){
	timer.set_one_shot(true);
	timer.set_wait_time(0.5f);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->set_enable_gravity(true);
		enemy->switch_state("dash_in_air");
		});
}

void EnemyAimState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("aim");
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_enable_gravity(false);
	enemy->set_velocity({ 0,0 });
	timer.restart();
}

void EnemyAimState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();

	timer.on_update(delta);

	if(enemy->get_hp()<=0)
		enemy->switch_state("dead");
}
