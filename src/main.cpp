#include <iostream>
#include <Windows.h>
#include "../include/Memory.hpp"
#include "../include/csgo.hpp"

using namespace std;
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

class Memory Memory;
uintptr_t client;
uintptr_t engine;
uintptr_t player;

bool cheatIsRunning = true;

void die(const char* msg) {
    cout << msg << endl;
    Sleep(3000);
    exit(-1);
}

int main() {

    uintptr_t csgo = Memory.GetProcessId("csgo.exe");
	if (csgo == NULL) die("Cannot find CSGO");
	cout << "Process found: " << csgo << endl;

    engine = Memory.GetModuleBase(csgo, "engine.dll");
	client = Memory.GetModuleBase(csgo, "client.dll");

	//if (!client || !engine) return 0;
	cout << "Engine module: " << engine << ", Client module: " << client << endl;

    uintptr_t client_state = Memory.read<uintptr_t>(engine+dwClientState);
    if (!client_state) return 0;
    cout << "Client state: " << client_state << endl;
	
    while (cheatIsRunning) {
		
		int playerIndex = Memory.read<uintptr_t>(client_state + dwClientState_GetLocalPlayer);
		player = Memory.read<uintptr_t>(client + dwEntityList + (playerIndex * 0x10) );

		//TODO: Add handlers

        if (GetAsyncKeyState(VK_F8) & 1) {
            cheatIsRunning = false;
        }
    }

	return 0;
}