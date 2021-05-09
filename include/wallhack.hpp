#pragma once
#include <Windows.h>
#include "csgo.hpp"
#include "Memory.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

struct GlowStruct {
    BYTE base[4];
    float red;
    float green;
    float blue;
    float alpha;
    BYTE padding[16];
    bool renderWhenOccluded;
    bool renderWhenUnoccluded;
    BYTE fullbloom;
    BYTE padding2[5];
    int glowStyle;
};

struct ClrRender {
	BYTE red, green, blue;
};

extern class Memory Memory;
extern uintptr_t client;
extern uintptr_t engine;
extern uintptr_t player;

void handleBrightness();
void handleGlow();