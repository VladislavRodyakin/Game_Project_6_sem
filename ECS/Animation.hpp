#pragma once

struct Animation {
	int index, frames, frame_time;
	Animation() = default;
	Animation(int id, int fr, int fr_t) : 
		index(id), frames(fr), frame_time(fr_t) {
	}
};