#include "enemy_squat_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"
#include "../../characters/player.h"

EnemySquatState::EnemySquatState(){
	timer.set_one_shot(true);
	timer.set_wait_time(0.5f);
	timer.set_on_timeout([&] {
		Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
		enemy->switch_state("dash_on_floor");
		});
}

void EnemySquatState::on_enter(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();

	const Vector2& pos_enemy = enemy->get_position();
	const Vector2& pos_player = player->get_position();

	enemy->set_animation("squat");
	enemy->set_facing_left(pos_enemy.x > pos_player.x);

	timer.restart();
}

void EnemySquatState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();

	timer.on_update(delta);

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}
}
