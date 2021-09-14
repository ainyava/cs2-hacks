#include <iostream>
#include <Windows.h>
#include "../include/Memory.hpp"
#include "../include/csgo.hpp"
#include "../include/wallhack.hpp"
#include "../include/bhop.hpp"
#include "../include/triggerbot.hpp"

using namespace std;
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

class Memory Memory;
uint32_t client;
uint32_t engine;
uint32_t player;

bool cheatIsRunning = true;

void die(const char* msg) {
    cout << msg << endl;
    Sleep(3000);
    exit(-1);
}

int main() {

    uint32_t csgo = Memory.GetProcessId("csgo.exe");
	if (!csgo) die("Cannot find CSGO");
	cout << "Process found: " << csgo << endl;

    engine = Memory.GetModuleBase(csgo, "engine.dll");
	client = Memory.GetModuleBase(csgo, "client.dll");

	//if (!client || !engine) return 0;
	cout << "Engine module: " << engine << ", Client module: " << client << endl;

    uint32_t client_state = Memory.read<uint32_t>(engine+dwClientState);
    if (!client_state) return 0;
    cout << "Client state: " << client_state << endl;

    handleBrightness();
	
    while (cheatIsRunning) {
		
		int playerIndex = Memory.read<uint32_t>(client_state + dwClientState_GetLocalPlayer);
		player = Memory.read<uint32_t>(client + dwEntityList + (playerIndex * 0x10) );

		handleGlow();
		handleBhop();
		handleTriggerBot();

        if (GetAsyncKeyState(VK_F8) & 1) {
            handleBrightness();
            cheatIsRunning = false;
        }
    }

	return 0;
}