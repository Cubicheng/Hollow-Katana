#include "character.h"
#include "../collision/collision_manager.h"

Character::Character() {
	hit_box = CollisionManager::getInstance()->create_collision_box();
	hurt_box = CollisionManager::getInstance()->create_collision_box();

	timer_invunlerable_status.set_wait_time(1.0f);
	timer_invunlerable_status.set_one_shot(true);
	timer_invunlerable_status.set_on_timeout(
		[&]() {
			is_invunlerable = false;
		}
	);

	timer_invunlerable_blink.set_wait_time(0.075f);
	timer_invunlerable_blink.set_one_shot(false);
	timer_invunlerable_blink.set_on_timeout(
		[&]() {
			is_blink_invisible = !is_blink_invisible;
		}
	);
}

Character::~Character() {
	CollisionManager::getInstance()->destroy_collision_box(hit_box);
	CollisionManager::getInstance()->destroy_collision_box(hurt_box);
}

void Character::decrease_hp() {
	if (is_invunlerable)
		return;
	hp--;
	if (hp > 0)
		make_invunlerable();
	on_hurt();
}

void Character::on_update(float delta) {
	state_machine.on_update(delta);
	if (hp <= 0)
		velocity.x = 0;
	if (enable_gravity)
		velocity.y += delta * GRAVITY;

	position += (velocity * delta);

	if (position.y >= FLOOR_Y) {
		position.y = FLOOR_Y;
		velocity.y = 0;
	}

	if (position.x <= 0)
		position.x = 0;
	if (position.x >= getwidth())
		position.x = getwidth();

	hurt_box->set_position(get_logic_center());

	timer_invunlerable_status.on_update(delta);
	if (is_invunlerable)
		timer_invunlerable_blink.on_update(delta);

	if (!current_animation)
		return;

	Animation& animation = is_facing_left ? current_animation->Left : current_animation->Right;
	animation.on_update(delta);
	animation.set_position(position);
}

void Character::on_render() {
	if (!current_animation || (is_invunlerable && !is_blink_invisible))
		return;
	Animation& animation = is_facing_left ? current_animation->Left : current_animation->Right;
	animation.on_render();
}

void Character::switch_state(const std::string& id) {
	state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id) {
	if (animation_pool.find(id) == animation_pool.end())
		__debugbreak();
	current_animation = &animation_pool[id];

	current_animation->Left.reset();
	current_animation->Right.reset();
}