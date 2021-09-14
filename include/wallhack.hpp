#pragma once
#include <Windows.h>
#include "csgo.hpp"
#include "Memory.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

struct GlowStruct {
	BYTE base[8];
	float red;
	float green;
	float blue;
	float alpha;
	BYTE padding[16];
	bool renderWhenOccluded;
	bool renderWhenUnoccluded;
};

struct ClrRender {
	BYTE red, green, blue;
};

extern class Memory Memory;
extern uint32_t client;
extern uint32_t engine;
extern uint32_t player;

void handleBrightness();
void handleGlow();