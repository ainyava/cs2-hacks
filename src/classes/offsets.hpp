#pragma once
#include <iostream>

namespace offsets {
	inline std::ptrdiff_t dwLocalPlayerController = 0x19115A8;
	inline std::ptrdiff_t dwEntityList = 0x18C1DE8;
	inline std::ptrdiff_t dwViewMatrix = 0x19231E0;
	inline std::ptrdiff_t dwBuildNumber = 0x515564;
	inline std::ptrdiff_t dwPlantedC4 = 0x1927A68;

	inline std::ptrdiff_t m_flC4Blow = 0xEB0;
	inline std::ptrdiff_t m_flNextBeep = 0xEAC;
	inline std::ptrdiff_t m_flTimerLength = 0xEB8;

	inline std::ptrdiff_t m_pInGameMoneyServices = 0x6D0;
	inline std::ptrdiff_t m_iAccount = 0x40;
	inline std::ptrdiff_t m_vecAbsOrigin = 0xC8;
	inline std::ptrdiff_t m_vOldOrigin = 0x1224;
	inline std::ptrdiff_t m_pGameSceneNode = 0x310;
	inline std::ptrdiff_t m_flFlashOverlayAlpha = 0x1444;
	inline std::ptrdiff_t m_bIsDefusing = 0x1390;
	inline std::ptrdiff_t m_szName = 0xC18;
	inline std::ptrdiff_t m_pClippingWeapon = 0x1290;
	inline std::ptrdiff_t m_ArmorValue = 0x14F0;
	inline std::ptrdiff_t m_iHealth = 0x32C;
	inline std::ptrdiff_t m_hPlayerPawn = 0x7BC;
	inline std::ptrdiff_t m_sSanitizedPlayerName = 0x720;
	inline std::ptrdiff_t m_iTeamNum = 0x3BF;
}