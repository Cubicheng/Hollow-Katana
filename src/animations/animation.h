#pragma once

#include "../util.h"
#include "../timer.h"
#include "../vector2.h"
#include "atlas.h"
#include <vector>
#include <iostream>

class Animation {
public:
	Animation() {
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]() {
				idx_frame++;
				if (idx_frame >= frames.size()) {
					idx_frame = is_loop ? 0 : frames.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);

	}
	~Animation() = default;

	enum class AnchorMode {
		Centered,
		BottomCentered
	};

	void reset() {
		idx_frame = 0;
		timer.restart();
	}

	void set_anchor_mode(AnchorMode mode) {
		anchor_mode = mode;
	}

	void set_position(const Vector2& pos) {
		position = pos;
	}

	void set_loop(bool is_loop) {
		this->is_loop = is_loop;
	}

	void set_interval(float interval) {
		timer.set_wait_time(interval);
	}

	void set_on_finished(std::function<void()> on_finished) {
		this->on_finished = on_finished;
	}

	void add_frame(IMAGE* img, int num_frames) {
		int width = img->getwidth();
		int height = img->getheight();
		int width_frame = width / num_frames;

		for (int i = 0; i < num_frames; i++) {
			ut::Rect rect_src;
			rect_src.x = width_frame * i;
			rect_src.y = 0;
			rect_src.w = width_frame;
			rect_src.h = height;
			frames.emplace_back(img, rect_src);
		}
	}

	void add_frame(Atlas* atlas) {
		for (int i = 0; i < atlas->get_size(); i++) {
			IMAGE* img = atlas->get_image(i);
			int width = img->getwidth();
			int height = img->getheight();

			ut::Rect rect_src;
			rect_src.x = 0;
			rect_src.y = 0;
			rect_src.w = width;
			rect_src.h = height;

			frames.emplace_back(img, rect_src);
		}
	}

	void on_update(float delta) {
		timer.on_update(delta);
	}

	void on_render() {
		const Frame &frame = frames[idx_frame];
		ut::Rect rect_dst;
		rect_dst.x = (int)position.x - frame.rect.w / 2;
		if(anchor_mode==AnchorMode::BottomCentered)
			rect_dst.y = (int)position.y - frame.rect.h;
		else
			rect_dst.y = (int)position.y - frame.rect.h/2;
		
		rect_dst.w = frame.rect.w;
		rect_dst.h = frame.rect.h;

		//setlinecolor(RGB(0, 255, 0));
		//rectangle((int)(rect_dst.x),
		//	(int)(rect_dst.y),
		//	(int)(rect_dst.x + rect_dst.w),
		//	(int)(rect_dst.y + rect_dst.h));

		ut::putimage_ex(frame.img, &rect_dst, &frame.rect);
	}

	int get_height() const {
		return frames[0].rect.h;
	}

	int get_width() const {
		return frames[0].rect.w;
	}

private:
	struct Frame {
		ut::Rect rect;
		IMAGE* img = nullptr;

		Frame() = default;
		Frame(IMAGE* img,const ut::Rect &rect):img(img),rect(rect){}

		~Frame() = default;
	};

	Timer timer;
	Vector2 position;
	bool is_loop = true;
	size_t idx_frame = 0;
	std::vector<Frame> frames;
	std::function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::Centered;
};