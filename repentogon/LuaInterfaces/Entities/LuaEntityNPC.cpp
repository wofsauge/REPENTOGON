#include <vector>
#include <stdexcept>

#include "ASMPatcher.hpp"
#include "SigScan.h"
#include "IsaacRepentance.h"
#include "LuaCore.h"
#include "HookSystem.h"


struct FireProjectilesStorage {
	std::vector<Entity_Projectile*> projectiles;
	bool inUse = false;
};

thread_local FireProjectilesStorage projectilesStorage;

static std::vector<Entity_Projectile*>& InitProjectileStorage() {
	std::vector<Entity_Projectile*>& projectiles = projectilesStorage.projectiles;
	projectiles.clear();
	projectilesStorage.inUse = true;
	return projectiles;
}

LUA_FUNCTION(Lua_EntityNPC_UpdateDirtColor)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	bool lerp = lua::luaL_checkboolean(L, 2);

	npc->UpdateDirtColor(lerp);
	return 0;
}

LUA_FUNCTION(Lua_EntityNPC_GetDirtColor)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");

	ColorMod* toLua = lua::luabridge::UserdataValue<ColorMod>::place(L, lua::GetMetatableKey(lua::Metatables::COLOR));
	*toLua = *npc->GetDirtColor();

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_GetControllerId)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");

	lua_pushnumber(L, *npc->GetControllerId());

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_SetControllerId)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	int unk = (int)luaL_checknumber(L, 2);

	npc->SetControllerId(unk);
	return 0;
}

LUA_FUNCTION(Lua_EntityNPC_TryForceTarget) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Entity* target = lua::GetUserdata<Entity*>(L, 2, lua::Metatables::ENTITY, "Entity");
	int duration = (int)luaL_checkinteger(L, 3);

	lua_pushboolean(L, npc->TryForceTarget(target, duration));
	return 1;
}

static void ProjectileStorageToLua(lua_State* L, std::vector<Entity_Projectile*>& projectiles) {
	lua_newtable(L);
	for (size_t i = 0; i < projectiles.size(); ++i) {
		lua_pushinteger(L, i + 1);
		lua::luabridge::UserdataPtr::push(L, projectiles[i], lua::GetMetatableKey(lua::Metatables::ENTITY_PROJECTILE));
		lua_rawset(L, -3);
	}

	projectilesStorage.projectiles.clear();
	projectilesStorage.inUse = false;
}

LUA_FUNCTION(Lua_EntityNPC_FireProjectilesEx) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* position = lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	Vector* velocity = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	uint32_t mode = (uint32_t)luaL_checkinteger(L, 4);

	if (mode > 9) {
		return luaL_error(L, "Invalid projectile mode %u\n", mode);
	}

	ProjectileParams* params = lua::GetUserdata<ProjectileParams*>(L, 5, lua::Metatables::PROJECTILE_PARAMS, "ProjectileParams");

	std::vector<Entity_Projectile*>& projectiles = InitProjectileStorage();
	npc->FireProjectiles(position, velocity, mode, params);
	ProjectileStorageToLua(L, projectiles);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_FireBossProjectilesEx) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	int numProjectiles = (int)luaL_checkinteger(L, 2);

	if (numProjectiles <= 0) {
		return luaL_error(L, "Invalid amount of projectiles %d\n", numProjectiles);
	}

	Vector* targetPos = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	float trajectoryModifier = (float)luaL_checknumber(L, 4);
	ProjectileParams* params = lua::GetUserdata<ProjectileParams*>(L, 5, lua::Metatables::PROJECTILE_PARAMS, "ProjectileParams");

	std::vector<Entity_Projectile*>& projectiles = InitProjectileStorage();
	npc->FireBossProjectiles(numProjectiles, *targetPos, trajectoryModifier, *params);
	ProjectileStorageToLua(L, projectiles);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_GetHitList) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	std::vector<unsigned int> hitList = npc->GetHitList();

	lua_newtable(L);
	int idx = 1;
	for (int index : hitList) {
		lua_pushnumber(L, idx);
		lua_pushinteger(L, index);
		lua_settable(L, -3);
		idx++;
	}

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_GetShieldStrength)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");

	lua_pushnumber(L, *npc->GetShieldStrength());

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_SetShieldStrength)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");

	*npc->GetShieldStrength() = (float)luaL_checknumber(L, 2);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_PlaySound)
{
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	int id = (int)luaL_checkinteger(L, 2);
	float volume = (float)luaL_optnumber(L, 3, 1.0);
	int framedelay = (int)luaL_optinteger(L, 4, 2);
	bool loop = lua::luaL_optboolean(L, 5, false);
	float pitch = (float)luaL_optnumber(L, 6, 1.0);

	npc->PlaySound(id, volume, framedelay, loop, pitch);

	return 0;
}

LUA_FUNCTION(Lua_EntityNPC_GetV1) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	lua::luabridge::UserdataPtr::push(L, &npc->_v1, lua::Metatables::VECTOR);
	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_GetV2) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	lua::luabridge::UserdataPtr::push(L, &npc->_v2, lua::Metatables::VECTOR);
	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_FireGridEntity) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	ANM2* sprite = lua::GetUserdata<ANM2*>(L, 2, lua::Metatables::SPRITE, "Sprite");
	GridEntityDesc* desc = lua::GetUserdata<GridEntityDesc*>(L, 3, lua::Metatables::GRID_ENTITY_DESC, "GridEntityDesc");
	Vector* velocity = lua::GetUserdata<Vector*>(L, 4, lua::Metatables::VECTOR, "Vector");
	int backdrop = min((int)luaL_optinteger(L, 5, g_Game->_room->GetBackdrop()->backdropId), 1);

	lua::luabridge::UserdataPtr::push(L, npc->FireGridEntity(sprite, desc, velocity, backdrop), lua::Metatables::ENTITY_PROJECTILE);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_MakeBloodCloud) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector pos = *npc->GetPosition();
	if (lua_type(L, 2) == LUA_TUSERDATA) {
		pos = *lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	}

	ColorMod color;
	if (lua_type(L, 3) == LUA_TUSERDATA) {
		color = *lua::GetUserdata<ColorMod*>(L, 3, lua::Metatables::COLOR, "Color");
	}

	lua::luabridge::UserdataPtr::push(L, npc->MakeBloodCloud(&pos, &color), lua::Metatables::ENTITY_EFFECT);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_MakeBloodSplash) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	npc->MakeBloodSplash();

	return 0;
}

LUA_FUNCTION(Lua_EntityNPC_ThrowMaggot) {
	//Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Vector* target = lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	float yOffset = (float)luaL_optnumber(L, 3, -10.0f);
	float fallSpeed = (float)luaL_optnumber(L, 4, -8.0f);

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ThrowMaggot(origin, target, yOffset, fallSpeed), lua::Metatables::ENTITY_NPC);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_ThrowMaggotAtPos) {
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Vector* target = lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	float yOffset = (float)luaL_optnumber(L, 3, -8.0f);

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ThrowMaggotAtPos(origin, target, yOffset), lua::Metatables::ENTITY_NPC);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_ShootMaggotProjectile) {
	//Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Vector* target = lua::GetUserdata<Vector*>(L, 2, lua::Metatables::VECTOR, "Vector");
	float velocity = (float)luaL_optnumber(L, 3, -24.0f);
	float yOffset = (float)luaL_optnumber(L, 4, -8.0f);

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ShootMaggotProjectile(origin, target, velocity, yOffset), lua::Metatables::ENTITY_NPC);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_TryThrow) {
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	EntityRef* ref = lua::GetUserdata<EntityRef*>(L, 2, lua::Metatables::ENTITY_REF, "EntityRef");
	Vector* dir = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	const float force = (float)luaL_checknumber(L, 4);
	lua_pushboolean(L, npc->TryThrow(*ref, dir, force));
	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_ThrowStrider) {
	//Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Entity* entity = nullptr;
	if (lua_type(L, 2) == LUA_TUSERDATA) {
		entity = lua::GetUserdata<Entity*>(L, 2, lua::Metatables::ENTITY, "Entity");
	}

	Vector* target = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ThrowStrider(origin, entity, target), lua::Metatables::ENTITY_NPC);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_ThrowRockSpider) {
	//Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Entity* entity = nullptr;
	if (lua_type(L, 2) == LUA_TUSERDATA) {
		entity = lua::GetUserdata<Entity*>(L, 2, lua::Metatables::ENTITY, "Entity");
	}

	Vector* target = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	const int variant = (int)luaL_optinteger(L, 4, 0);
	const float yPosOffset = (float)luaL_optnumber(L, 5, -10.0f);

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ThrowRockSpider(origin, target, entity, variant, yPosOffset), lua::Metatables::ENTITY_NPC);

	return 1;
}

LUA_FUNCTION(Lua_EntityNPC_ThrowLeech) {
	//Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	Vector* origin = lua::GetUserdata<Vector*>(L, 1, lua::Metatables::VECTOR, "Vector");
	Entity* entity = nullptr;
	if (lua_type(L, 2) == LUA_TUSERDATA) {
		entity = lua::GetUserdata<Entity*>(L, 2, lua::Metatables::ENTITY, "Entity");
	}

	Vector* target = lua::GetUserdata<Vector*>(L, 3, lua::Metatables::VECTOR, "Vector");
	const float yPosOffset = (float)luaL_optnumber(L, 4, -10.0f);
	bool big = lua::luaL_optboolean(L, 5, false);

	lua::luabridge::UserdataPtr::push(L, Entity_NPC::ThrowLeech(origin, entity, yPosOffset, target, big), lua::Metatables::ENTITY_NPC);

	return 1;
}

/*
// gonna make a minecart metatable later
LUA_FUNCTION(Lua_EntityNPC_Minecart_UpdateChild) {
	Entity_NPC* cart = lua::GetUserdata<Entity_NPC*>(L, 1, lua::Metatables::ENTITY_NPC, "EntityNPC");
	if (cart->_type != 965) {
		return luaL_error("Must be called with a minecart NPC!");
	}
	Entity_NPC* npc = lua::GetUserdata<Entity_NPC*>(L, 2, lua::Metatables::ENTITY_NPC, "EntityNPC");
	cart->MinecartUpdateChild(npc);

	return 0;
}*/


HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua::LuaStackProtector protector(_state);

	luaL_Reg functions[] = {
		{ "PlaySound", Lua_EntityNPC_PlaySound },
		{ "SpawnBloodCloud", Lua_EntityNPC_MakeBloodCloud },
		{ "SpawnBloodSplash", Lua_EntityNPC_MakeBloodSplash },
		{ "UpdateDirtColor", Lua_EntityNPC_UpdateDirtColor },
		{ "GetDirtColor", Lua_EntityNPC_GetDirtColor },
		{ "GetControllerId", Lua_EntityNPC_GetControllerId },
		{ "SetControllerId", Lua_EntityNPC_SetControllerId },
		{ "TryForceTarget", Lua_EntityNPC_TryForceTarget },
		{ "FireGridEntity", Lua_EntityNPC_FireGridEntity },
		{ "FireProjectilesEx", Lua_EntityNPC_FireProjectilesEx },
		{ "FireBossProjectilesEx", Lua_EntityNPC_FireBossProjectilesEx },
		{ "GetHitList", Lua_EntityNPC_GetHitList },
		{ "GetShieldStrength", Lua_EntityNPC_GetShieldStrength },
		{ "SetShieldStrength", Lua_EntityNPC_SetShieldStrength },
		//{ "ThrowMaggot", Lua_EntityNPC_ThrowMaggot },
		//{ "ThrowMaggotAtPos", Lua_EntityNPC_ThrowMaggotAtPos },
		{ "TryThrow", Lua_EntityNPC_TryThrow },
		// Minecart
		//{ "MinecartUpdateChild", Lua_EntityNPC_Minecart_UpdateChild },
		{ NULL, NULL }
	};
	lua::RegisterFunctions(_state, lua::Metatables::ENTITY_NPC, functions);

	/* Fix V1 and V2 not being pointers. */
	lua::RegisterVariableGetter(_state, lua::Metatables::ENTITY_NPC, "V1", Lua_EntityNPC_GetV1);
	lua::RegisterVariableGetter(_state, lua::Metatables::ENTITY_NPC, "V2", Lua_EntityNPC_GetV2);

	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ThrowMaggot", Lua_EntityNPC_ThrowMaggot);
	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ThrowMaggotAtPos", Lua_EntityNPC_ThrowMaggotAtPos);
	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ShootMaggotProjectile", Lua_EntityNPC_ShootMaggotProjectile);
	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ThrowStrider", Lua_EntityNPC_ThrowStrider);
	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ThrowRockSpider", Lua_EntityNPC_ThrowRockSpider);
	lua::RegisterGlobalClassFunction(_state, "EntityNPC", "ThrowLeech", Lua_EntityNPC_ThrowLeech);
}

void __stdcall FireProjectilesEx_Internal(std::vector<Entity_Projectile*> const& projectiles) {
	if (!projectilesStorage.inUse) {
		return;
	}

	for (Entity_Projectile* projectile : projectiles) {
		projectilesStorage.projectiles.push_back(projectile);
	}
}

void __stdcall FireBossProjectilesEx_Internal(Entity_Projectile* projectile) {
	if (!projectilesStorage.inUse) {
		return;
	}

	projectilesStorage.projectiles.push_back(projectile);
}

void PatchFireProjectiles() {
	const char* signature = "33c92b55b4c1fa02894ddc8955e4";
	SigScan scanner(signature);
	scanner.Scan();
	void* addr = scanner.GetAddress();

	using Reg = ASMPatch::SavedRegisters::Registers;
	using GPReg = ASMPatch::Registers;

	ASMPatch patch;
	ASMPatch::SavedRegisters registers(Reg::EAX | Reg::EBX | Reg::ECX | Reg::EDX | Reg::EDI | Reg::ESI |
		Reg::XMM0 | Reg::XMM1 | Reg::XMM2 | Reg::XMM3 | Reg::XMM4 | Reg::XMM5, true);
	patch.PreserveRegisters(registers);
	// patch.MoveFromMemory(GPReg::EBP, -0x4C, GPReg::ESI, true);
	patch.LoadEffectiveAddress(GPReg::EBP, -0x4C, GPReg::ESI);
	patch.Push(GPReg::ESI);
	patch.AddInternalCall(FireProjectilesEx_Internal);
	patch.RestoreRegisters(registers);
	patch.AddBytes("\x33\xc9\x2b\x55\xb4");
	patch.AddRelativeJump((char*)addr + 0x5);

	sASMPatcher.PatchAt(addr, &patch);
}

void PatchFireBossProjectiles() {
	const char* signature = "f30f104424388bf883c414";
	SigScan scanner(signature);
	scanner.Scan();
	void* addr = scanner.GetAddress();

	using Reg = ASMPatch::SavedRegisters::Registers;
	using GPReg = ASMPatch::Registers;

	ASMPatch patch;
	ASMPatch::SavedRegisters registers(Reg::GP_REGISTERS_STACKLESS | Reg::XMM0 | Reg::XMM1 | Reg::XMM2 | Reg::XMM3, true);
	patch.PreserveRegisters(registers);
	patch.Push(GPReg::EAX);
	patch.AddInternalCall(FireBossProjectilesEx_Internal);
	patch.RestoreRegisters(registers);
	patch.AddBytes("\xF3\x0f\x10\x44\x24\x38");
	patch.AddRelativeJump((char*)addr + 0x6);

	sASMPatcher.PatchAt(addr, &patch);
}
