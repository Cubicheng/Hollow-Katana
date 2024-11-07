#include "enemy_dead_state.h"
#include "graphics.h"

void EnemyDeadState::on_enter(){
	MessageBox(GetHWnd(), _T("很好，这样能行。"), _T("挑战成功！"), MB_OK);
	exit(0);
}
