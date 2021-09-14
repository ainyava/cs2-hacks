#include "../include/wallhack.hpp"

bool espIsOn = false;

void handleBrightness() {
	float brightness = 5;
	uint32_t ptr = Memory.read<uint32_t>(engine + model_ambient_min);
	ptr = *(int*)&brightness ^ ptr;
	Memory.write<uint32_t>(engine + model_ambient_min, ptr);
}

void handleGlow() {
	if (GetAsyncKeyState(VK_F1) & 1) {
		espIsOn = !espIsOn;
	}

	if (espIsOn || GetAsyncKeyState('F') == -32768) {
		uint32_t glowObject = Memory.read<uint32_t>(client + dwGlowObjectManager);
		int myTeam = Memory.read<int>(player + m_iTeamNum);

		for (short int i = 0; i < 64; i++) {
			uint32_t entity = Memory.read<uint32_t>(client + dwEntityList + (i * 0x10));
			if (entity) {

				int entityTeam = Memory.read<int>(entity + m_iTeamNum);
				int glowIndex = Memory.read<int>(entity + m_iGlowIndex);
				int health = Memory.read <int>(entity + m_iHealth);
				bool isDefusing = Memory.read<bool>(entity + m_bIsDefusing);

				GlowStruct entityGlow = Memory.read<GlowStruct>(glowObject + (glowIndex * 0x38));
				ClrRender entityClr = Memory.read<ClrRender>(entity + m_clrRender);

				if (isDefusing) {
					entityGlow.red = 1;
					entityGlow.green = 1;
					entityGlow.blue = 1;
				}
				else if (myTeam == entityTeam) {
					entityGlow.blue = 1;
					entityClr.blue = 255;
					entityClr.red = 0;
				}
				else {
					entityGlow.red = (100 - health) / 100.0;
					entityGlow.green = health / 100.0;
					entityClr.blue = 0;
					entityClr.red = 255;
				}
				entityClr.green = 0;
				entityGlow.alpha = 1;
				entityGlow.renderWhenOccluded = true;
				entityGlow.renderWhenUnoccluded = false;
				Memory.write<GlowStruct>(glowObject + (glowIndex * 0x38), entityGlow);
				Memory.write<ClrRender>(entity + m_clrRender, entityClr);
			}
		}
	}
}