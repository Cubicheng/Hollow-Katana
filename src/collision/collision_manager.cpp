#include "collision_manager.h"
#include <algorithm>
#include <graphics.h>

CollisionManager* CollisionManager::manager = nullptr;

CollisionManager* CollisionManager::getInstance(){
    if (!manager)
        manager = new CollisionManager();
    return manager;
}

CollisionBox* CollisionManager::create_collision_box(){
    CollisionBox* box = new CollisionBox();
    collision_box_list.push_back(box);
    return box;
}

void CollisionManager::destroy_collision_box(CollisionBox* collision_box){
    collision_box_list.erase(std::remove(collision_box_list.begin(), collision_box_list.end(), collision_box), collision_box_list.end());
    delete collision_box;
}

void CollisionManager::process_collisions(){
    for (CollisionBox* src : collision_box_list) {
        if (!src->enabled || src->layer_dst == CollisionLayer::None)
            continue;
        for (CollisionBox* dst : collision_box_list) {
            if(!dst->enabled || dst==src || src->layer_dst != dst->layer_src)
                continue;

            bool is_collid_x =
                (max(src->position.x + src->get_size().x / 2, dst->position.x + dst->get_size().x / 2)
                    - min(src->position.x - src->get_size().x / 2, dst->position.x - dst->get_size().x / 2)
                    <= src->get_size().x + dst->get_size().x);

            bool is_collid_y =
                (max(src->position.y + src->get_size().y / 2, dst->position.y + dst->get_size().y / 2)
                    - min(src->position.y - src->get_size().y / 2, dst->position.y - dst->get_size().y / 2)
                    <= src->get_size().y + dst->get_size().y);

            if (is_collid_x && is_collid_y && dst->onCollision)
                dst->onCollision();
        }

    }
}

void CollisionManager::on_debug_render(){
    for (CollisionBox* box : collision_box_list) {
        if (!box->enabled) continue;
        setlinecolor(box->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
        rectangle((int)(box->position.x - box->size.x / 2),
            (int)(box->position.y - box->size.y / 2),
            (int)(box->position.x + box->size.x / 2),
            (int)(box->position.y + box->size.y / 2));
    }
}
