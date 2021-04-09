#include "../include/triggerbot.hpp"

bool triggerBotIsOn = false;

void handleTriggerBot() {
	if (GetAsyncKeyState(VK_F3) & 1) {
		triggerBotIsOn = !triggerBotIsOn;
	}

	if (triggerBotIsOn) {
		int crosshair = Memory.read<int>(player + m_iCrosshairId);
		int myTeam = Memory.read<int>(player + m_iTeamNum);
		uint32_t entity = Memory.read<uint32_t>(client + dwEntityList + (crosshair-1) * 0x10);
		int team = Memory.read<int>(entity + m_iTeamNum);
		int health = Memory.read<int>(entity + m_iHealth);
		if (myTeam != team && health > 0) {
			Memory.write<int>(client + dwForceAttack, 5);
			Sleep(20);
			Memory.write<int>(client + dwForceAttack, 4);
		}
	};
}