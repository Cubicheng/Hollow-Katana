#include "enemy_throw_barb_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"
#include "../../characters/player.h"

EnemyThrowBarbState::EnemyThrowBarbState(){
	timer.set_one_shot(true);
	timer.set_wait_time(0.8f);
	timer.set_on_timeout([&]() {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->throw_barbs();
		enemy->switch_state("idle");
		});
}

void EnemyThrowBarbState::on_enter(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_animation("throw_barb");
	timer.restart();

	ut::play_audio(_T("enemy_throw_barbs"), false);
}

void EnemyThrowBarbState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
}




