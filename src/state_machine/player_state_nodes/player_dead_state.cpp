#include "player_dead_state.h"
#include "graphics.h"
#include "../../util.h"
#include "../../characters/character_manager.h"

PlayerDeadState::PlayerDeadState(){
	timer.set_wait_time(2.0f);
	timer.set_one_shot(true);
	timer.set_on_timeout(
		[&]() {
			MessageBox(GetHWnd(), _T("不对……\n这样不行。"), _T("挑战失败!"), MB_OK);
			exit(0);
		}
	);
}

void PlayerDeadState::on_enter(){
	Player* player = (Player*)CharacterManager::GetInstance()->GetPlayer();
	player->set_animation("dead");
	//ut::play_audio(_T("player_dead"), false);
}

void PlayerDeadState::on_update(float delta){
	timer.on_update(delta);
}
