#include "enemy_dead_state.h"
#include "graphics.h"

void EnemyDeadState::on_enter(){
	MessageBox(GetHWnd(), _T("�ܺã��������С�"), _T("��ս�ɹ���"), MB_OK);
	exit(0);
}
