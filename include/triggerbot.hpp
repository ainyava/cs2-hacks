#pragma once
#include "csgo.hpp"
#include "Memory.hpp"

using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

extern class Memory Memory;
extern uint32_t client;
extern uint32_t player;

void handleTriggerBot();