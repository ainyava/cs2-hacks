#pragma once
#include "../include/bhop.hpp"

bool bhopIsOn = true;

bool isPlayerMoving() {
	PlayerVector playerVec = Memory.read<PlayerVector>(player + m_vecVelocity);
	return playerVec.x + playerVec.y + playerVec.z != 0;
}

void handleBhop() {
	if (GetAsyncKeyState(VK_F2) & 1) {
		bhopIsOn = !bhopIsOn;
	}

	if (bhopIsOn) {
		if (isPlayerMoving()) {
			int flag = Memory.read<int>(player + m_fFlags);
			if ( flag & (1 << 0) && GetAsyncKeyState(VK_SPACE) == -32768) {
				Memory.write<int>(client + dwForceJump, 6);
			}
		}
	}
}