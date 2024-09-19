#include "resources_manager.h"
#include "util.h"

struct ImageResInfo {
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo {
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

static const std::vector<ImageResInfo> image_info_list = {
	{"background",_T("resources/background.png")},
	{"ui_heart",_T("resources/ui_heart.png")},

	{"player_attack_right",_T("resources/player/attack.png")},
	{"player_dead_right",_T("resources/player/dead.png")},
	{"player_fall_right",_T("resources/player/fall.png")},
	{"player_idle_right",_T("resources/player/idle.png")},
	{"player_jump_right",_T("resources/player/jump.png")},
	{"player_run_right",_T("resources/player/run.png")},
	{"player_roll_right",_T("resources/player/roll.png")},

	{"player_vfx_attack_dowm",_T("resources/player/vfx_attack_down.png")},
	{"player_vfx_attack_left",_T("resources/player/vfx_attack_left.png")},
	{"player_vfx_attack_right",_T("resources/player/vfx_attack_right.png")},
	{"player_vfx_attack_up",_T("resources/player/vfx_attack_up.png")},
	{"player_vfx_jump",_T("resources/player/vfx_jump.png")},
	{"player_vfx_land",_T("resources/player/vfx_land.png")}
};

static const std::vector<AtlasResInfo> atlas_info_list = {
	{"barb_break",_T("resources/enemy/barb_break/%d.png"),3},
	{"barb_loose",_T("resources/enemy/barb_loose/%d.png"),5},
	{"silk",_T("resources/enemy/silk/%d.png"),9},
	{"sword_left",_T("resources/enemy/sword/%d.png"),3},

	{"enemy_aim_left",_T("resources/enemy/aim/%d.png"),9},
	{"enemy_dash_in_air_left",_T("resources/enemy/dash_in_air/%d.png"),2},
	{"enemy_dash_on_floor_left",_T("resources/enemy/dash_on_floor/%d.png"),2},
	{"enemy_fall_left",_T("resources/enemy/fall/%d.png"),4},
	{"enemy_idle_left",_T("resources/enemy/idle/%d.png"),6},
	{"enemy_jump_left",_T("resources/enemy/jump/%d.png"),8},
	{"enemy_run_left",_T("resources/enemy/run/%d.png"),8},
	{"enemy_squat_left",_T("resources/enemy/squat/%d.png"),10},
	{"enemy_throw_barb_left",_T("resources/enemy/throw_barb/%d.png"),8},
	{"enemy_throw_silk_left",_T("resources/enemy/throw_silk/%d.png"),17},
	{"enemy_throw_sword_left",_T("resources/enemy/throw_sword/%d.png"),16},

	{"enemy_vfx_dash_in_air_left",_T("resources/enemy/vfx_dash_in_air/%d.png"),5},
	{"enemy_vfx_dash_on_floor_left",_T("resources/enemy/vfx_dash_on_floor/%d.png"),6}
};

static inline bool check_img_valid(IMAGE* img) {
	return GetImageBuffer(img);
}

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::GetInstance() {
	if(!manager)
		manager = new ResourcesManager();
	return manager;
}

void ResourcesManager::load() {
	for (const auto& image_info : image_info_list) {
		IMAGE* image = new IMAGE();
		loadimage(image, image_info.path);
		if (!check_img_valid(image))
			throw image_info.path;
		imageMap[image_info.id] = image;
	}

	for (const auto& atlas_info : atlas_info_list) {
		Atlas* atlas = new Atlas();
		atlas->load(atlas_info.path, atlas_info.num_frame);
		for (int i = 0; i < atlas_info.num_frame; i++) {
			IMAGE* image = atlas->get_image(i);
			if (!check_img_valid(image))
				throw atlas_info.path;
		}
		atlasMap[atlas_info.id] = atlas;
	}


	flip_image("player_attack_right", "player_attack_left", 5);
	flip_image("player_dead_right",   "player_dead_left",   6);
	flip_image("player_fall_right",   "player_fall_left",   5); 
	flip_image("player_idle_right",   "player_idle_left",   5); 
	flip_image("player_jump_right",   "player_jump_left",   5); 
	flip_image("player_run_right",    "player_run_left",    10);
	flip_image("player_roll_right",   "player_roll_left",   7);

	flip_atlas("enemy_aim_left", "enemy_aim_right");
	flip_atlas("enemy_dash_in_air_left", "enemy_dash_in_air_right");
	flip_atlas("enemy_dash_on_floor_left", "enemy_dash_on_floor_right");
	flip_atlas("enemy_fall_left", "enemy_fall_right");
	flip_atlas("enemy_idle_left", "enemy_idle_right");
	flip_atlas("enemy_jump_left", "enemy_jump_right");
	flip_atlas("enemy_run_left", "enemy_run_right");
	flip_atlas("enemy_squat_left", "enemy_squat_right");
	flip_atlas("enemy_throw_barb_left", "enemy_throw_barb_right");
	flip_atlas("enemy_throw_silk_left", "enemy_throw_silk_right");
	flip_atlas("enemy_throw_sword_left", "enemy_throw_sword_right");
	
	flip_atlas("enemy_vfx_dash_in_air_left", "enemy_vfx_dash_in_air_right");
	flip_atlas("enemy_vfx_dash_on_floor_left", "enemy_vfx_dash_on_floor_right");


	ut::load_audio("resources/audio/bgm.mp3", "bgm");
	ut::load_audio("resources/audio/barb_break.mp3", "barb_break");
	ut::load_audio("resources/audio/bullet_time.mp3", "bullet_time");
	
	ut::load_audio("resources/audio/enemy_dash.mp3", "enemy_dash");
	ut::load_audio("resources/audio/enemy_run.mp3", "enemy_run");
	ut::load_audio("resources/audio/enemy_hurt1.mp3", "enemy_hurt1");
	ut::load_audio("resources/audio/enemy_hurt2.mp3", "enemy_hurt2");
	ut::load_audio("resources/audio/enemy_hurt3.mp3", "enemy_hurt3");
	ut::load_audio("resources/audio/throw_barbs.mp3", "throw_barbs");
	ut::load_audio("resources/audio/throw_silk.mp3", "throw_silk");
	ut::load_audio("resources/audio/throw_sword.mp3", "throw_sword");

	ut::load_audio("resources/audio/player_attack1.mp3", "player_attach1");
	ut::load_audio("resources/audio/player_attack2.mp3", "player_attach2");
	ut::load_audio("resources/audio/player_attack3.mp3", "player_attach3");
	ut::load_audio("resources/audio/player_dead.mp3", "player_dead");
	ut::load_audio("resources/audio/player_hurt.mp3", "player_hurt");
	ut::load_audio("resources/audio/player_jump.mp3", "player_jump");
	ut::load_audio("resources/audio/player_land.mp3", "player_land");
	ut::load_audio("resources/audio/player_roll.mp3", "player_roll");
	ut::load_audio("resources/audio/player_run.mp3", "player_run");
}

Atlas* ResourcesManager::getAtlas(const std::string& id) const{
	const auto& it = atlasMap.find(id);
	if(it==atlasMap.end())
		return nullptr;
	return it->second;
}

IMAGE* ResourcesManager::getImage(const std::string& id) const{
	const auto& it = imageMap.find(id);
	if (it == imageMap.end())
		return nullptr;
	return it->second;
}

ResourcesManager::ResourcesManager() = default;
ResourcesManager::~ResourcesManager() = default;

void ResourcesManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h){
	int w = src_image->getwidth();
	int h = src_image->getheight();
	int w_frame= w / num_h;
	Resize(dst_image, w, h);
	DWORD* src_buf = GetImageBuffer(src_image);
	DWORD* dst_buf = GetImageBuffer(dst_image);
	for (int i = 0; i < num_h; i++) {
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++) {
			for (int x = x_left; x < x_right; x++) {
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buf[idx_dst] = src_buf[idx_src];
			}
		}
	}
}

void ResourcesManager::flip_image(const std::string& src_id, const std::string& dst_id, int num_h){
	IMAGE* src_image = imageMap[src_id];
	IMAGE* dst_image = new IMAGE();

	flip_image(src_image, dst_image, num_h);

	imageMap[dst_id] = dst_image;
}

void ResourcesManager::flip_atlas(const std::string& src_id, const std::string& dst_id){
	Atlas* src_atlas = atlasMap[src_id];
	Atlas* dst_atlas = new Atlas();

	for (int i = 0; i < src_atlas->get_size(); i++) {
		IMAGE img_flipped;
		flip_image(src_atlas->get_image(i),&img_flipped);
		dst_atlas->add_image(img_flipped);
	}

	atlasMap[dst_id] = dst_atlas;
}