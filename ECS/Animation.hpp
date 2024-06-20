#pragma once

struct Animation {
	int index = 0, frames = 0, frame_time = 0;
	Animation() = default;
	Animation(int id, int fr, int fr_t) : 
		index(id), frames(fr), frame_time(fr_t) {
	}
};