#include "enemy_run_state.h"
#include "../../characters/character_manager.h"
#include "../../characters/enemy.h"
#include "../../characters/player.h"

void EnemyRunState::on_enter(){
	CharacterManager::GetInstance()->GetEnemy()->set_animation("run");

	//ut::play_audio(_T("enemy_run"), true);
}

void EnemyRunState::on_update(float delta){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	
	const Vector2& pos_enemy = enemy->get_position();
	const Vector2& pos_player = player->get_position();
	enemy->set_velocity({ pos_enemy.x < pos_player.x ? SPEED_RUN : -SPEED_RUN , 0 });

	if (enemy->get_hp() <= 0) {
		enemy->switch_state("dead");
	}else if(abs(pos_enemy.x-pos_player.x)<=MIN_DIS){
		int rand_num = ut::range_random(0, 100);
		if (enemy->get_hp() > 5) {
			if (rand_num <= 75) {
				enemy->switch_state("squat");//75%
			}
			else {
				enemy->switch_state("throw_silk");//25%
			}
		}
		else {
			if (rand_num <= 75) {
				enemy->switch_state("throw_silk");//75%
			}
			else {
				enemy->switch_state("squat");//25%
			}
		}
		//ut::stop_audio(_T("enemy_run"));
	}
}


void EnemyRunState::on_exit(){
	Enemy* enemy = (Enemy*)CharacterManager::GetInstance()->GetEnemy();
	enemy->set_velocity(Vector2(0, 0));
}
