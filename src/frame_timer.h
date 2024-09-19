#pragma once
#include <chrono>
#include <thread>

using namespace std::chrono;

class FrameTimer{
public:
	FrameTimer() = default;
	~FrameTimer() = default;

	void update() {
		frame_start = steady_clock::now();
	}

	void frame_sleep() {
		frame_end = steady_clock::now();
		nanoseconds sleep_time = frame_time - (frame_end - frame_start);
		if (sleep_time > nanoseconds(0)) {
			std::this_thread::sleep_for(sleep_time);
		}
	}

private:
	const nanoseconds frame_time = nanoseconds(1000000000 / 120);
	steady_clock::time_point frame_end, frame_start;
};