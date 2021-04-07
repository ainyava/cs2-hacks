#pragma once
#include "csgo.hpp"
#include "Memory.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

struct PlayerVector {
	float x, y, z;
};

extern class Memory Memory;
extern uintptr_t client;
extern uintptr_t player;

void handleBhop();