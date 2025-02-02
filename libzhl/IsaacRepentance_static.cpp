#include "IsaacRepentance.h"

bool Room::IsValidRailType(lua_Integer rail) {
	if (rail < 0) {
		return false;
	}
	else if (rail > RailType::RAIL_NONE) {
		return false;
	}
	else {
		return rail <= RailType::RAIL_CROSSING || 
			rail == RAIL_DOOR_LEFT || 
			rail == RAIL_DOOR_RIGHT || 
			rail == RAIL_DOOR_TOP || 
			rail == RAIL_DOOR_BOTTOM;
	}
}

bool RoomConfig::IsValidGridIndex(lua_Integer index, bool includeWalls) const {
	if (index < 0) {
		return false;
	}

	switch (Shape) {
	case ROOMSHAPE_1x1: {
		bool validWall = includeWalls && (index <= 15 || index % 15 == 0 || index % 15 == 14 || (index >= 120 && index <= 134));
		return validWall || index <= 119;
	}

	default:
		return true;
	}
}

void KAGE::_LogMessage(int flag, const char* fmt, ...) {
	char buffer[4096];
	va_list va;
	va_start(va, fmt);
	int n = vsnprintf(buffer, 4095, fmt, va);
	va_end(va);

	if (n >= 0) {
		LogMessage(flag, buffer);
	}
}

bool Game::IsErased(int type, int variant, int subtype) {
	for (EntityId const& entity : _erasedEntities) {
		if (entity.type == type) {
			if (variant == -1) {
				return true;
			}
			else {
				if (entity.variant == variant) {
					if (subtype == -1) {
						return true;
					}
					else {
						return entity.subtype == subtype;
					}
				}
			}
		}
	}

	return false;
}

float Room::GetChampionBossChance() const {
	PersistentGameData* data = g_Manager->GetPersistentGameData();
	float chance = 0.f;
	bool subcond = g_Manager->GetState() == 2 && (g_Game->GetDailyChallenge()._id != 0 || g_Game->_isDebug);

	if (data->achievements[0x3] || subcond) { /* Womb unlock */
		chance = 0.1f;

		if (data->achievements[0x21] || subcond) { /* ??? unlock */
			chance = 0.3f;
		}

		if (g_Game->_difficulty == 3) { /* Greedier */
			chance = 0.6f;
		}

		Entity_Player* player = g_Game->GetPlayerManager()->FirstTrinketOwner(TRINKET_PURPLE_HEART, NULL, true);
		if (player) {
			int mult = g_Game->GetPlayerManager()->GetTrinketMultiplier(TRINKET_PURPLE_HEART);
			chance *= (mult * 2);
		}

		if (g_Game->GetChallenge() == 0x22) { /* Ultra Hard */
			chance = 1.f;
		}
	}

	return chance;
}

bool Room::IsChampionBossSeed() const {
	RNG rng;
	rng._seed = _descriptor->SpawnSeed;
	rng._shift1 = 0x1;
	rng._shift2 = 0xb;
	rng._shift3 = 0x10;

	float random = rng.RandomFloat();
	return random <= GetChampionBossChance();
}

bool ItemConfig::IsValidTrinket(unsigned int TrinketType) {
	if (TrinketType != 0 && (TrinketType & 0x7fff) < g_Manager->GetItemConfig()->GetTrinkets()->size()) {
		if (g_Manager->GetItemConfig()->GetTrinket(TrinketType & 0x7fff) != nullptr) {
			return true;
		}
	}

	return false;
}

bool Isaac::IsInGame() {
	return g_Manager->GetState() == 2 && g_Game;
}