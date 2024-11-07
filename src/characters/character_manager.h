#pragma once

#include "character.h"
#include "player.h"
#include "enemy.h"

class CharacterManager
{
public:
	static CharacterManager* GetInstance();

	Character* GetPlayer() {
		return player;
	}
	Character* GetEnemy() {
		return enemy;
	}

	void on_input(const ExMessage& msg);
	void on_update(float delta);
	void on_render();


private:

	static CharacterManager* manager;
	Character* player = nullptr;
	Character* enemy = nullptr;

	CharacterManager();
	~CharacterManager();
};