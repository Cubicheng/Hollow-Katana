#pragma once
#include <chrono>
#include <thread>

using namespace std::chrono;

class FrameTimer{
public:
	FrameTimer() = default;
	~FrameTimer() = default;

	void init() {
		last_tick_time = steady_clock::now();
	}

	void on_frame_start() {
		frame_start_time = steady_clock::now();
	}

	void on_frame_tick() {
		current_tick_time = steady_clock::now();
		delta = duration<float>(current_tick_time - last_tick_time);
	}

	void frame_sleep() {
		last_tick_time = current_tick_time;
		nanoseconds sleep_time = frame_time - (steady_clock::now() - frame_start_time);
		if (sleep_time > nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_time);
		}
	}

	const duration<float>& get_delta() const {
		return delta;
	}

private:
	const nanoseconds frame_time = nanoseconds(1000000000 / 120);
	steady_clock::time_point last_tick_time;
	steady_clock::time_point current_tick_time;
	steady_clock::time_point frame_start_time;
	steady_clock::time_point frame_end_time;
	duration<float> delta;
};