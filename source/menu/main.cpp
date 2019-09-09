
typedef unsigned char uchar;

#include <interface.h>
#include <cdll_int.h>
#include <GarrysMod/Lua/Interface.h>
#include <string.h>

#include "luaInterface.h"
#include "conv.h"
#include "shared.h"

#include "vtable.h"

using namespace GarrysMod;

Lua::Shared* luaShared;

VTable *luashared_vt;
VTable *client_vt;

Lua::Interface *cState;
Lua::ILuaBase *MENU;

int CallOnClient(lua_State *state)
{
	if (!cState)
		LUA->ThrowError("Not in game");
	
	//Lua::ILuaBase *CLIENT = cState->state->luabase;

	//CLIENT->PushSpecial(Lua::SPECIAL_GLOB);
	//CLIENT->GetField(-1, "hook");
	//CLIENT->GetField(-1, "Call");
	//CLIENT->PushString(LUA->GetString(1));
	//CLIENT->PushNil();
	//CLIENT->PushString(LUA->GetString(2));
	//CLIENT->Call(3, 1);
	//CLIENT->Pop(2);

	return 0;
}

int CallOnMenu(lua_State *state)
{
	const char *name = LUA->GetString(1);
	const char *data = LUA->GetString(2);
	if (!cState)
		LUA->ThrowError("Not in game");
	//MENU->PushSpecial(Lua::SPECIAL_GLOB);
	//MENU->GetField(-1, "hook");
	//MENU->GetField(-1, "Call");
	//MENU->PushString(name, strlen(name));
	//MENU->PushNil();
	//MENU->PushString(data, strlen(data));
	//MENU->Call(3, 1);
	//MENU->Pop(2);
	return 0;
}


typedef Lua::Interface *(__thiscall *hCreateLuaInterfaceFn)(Lua::Shared*, unsigned char, bool);
void *__hook hCreateLuaInterface(Lua::Shared *ths, HOOK_EDX(void *) uchar state, bool renew)
{
	Lua::Interface* hState = hCreateLuaInterfaceFn(luashared_vt->getold(Lua::Shared::CREATELUAINTERFACE))(ths, state, renew);

	if (state != Lua::Interface::CLIENT)
		return hState;

	cState = hState;

	//Push CallOnMenu to Client state

	client_vt = new VTable(cState);

	return cState;
}

typedef void *(__thiscall *hCloseLuaInterfaceFn)(Lua::Shared *, Lua::Interface *);
void *__hook hCloseLuaInterface(Lua::Shared *ths, HOOK_EDX(void *) Lua::Interface *iface)
{
	if (iface == cState)
		cState = NULL;

	return hCloseLuaInterfaceFn(luashared_vt->getold(Lua::Shared::CLOSELUAINTERFACE))(ths, iface);
}

GMOD_MODULE_OPEN()
{
	MENU = LUA;
	luaShared = GetInterface<Lua::Shared*>("lua_shared", "LUASHARED003");

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
		LUA->PushString("CallOnClient");
		LUA->PushCFunction(CallOnClient);
		LUA->SetTable(-3);
	LUA->Pop();

	luashared_vt = new VTable(luaShared);
	luashared_vt->hook(Lua::Shared::CREATELUAINTERFACE, (void *)&hCreateLuaInterface);
	luashared_vt->hook(Lua::Shared::CLOSELUAINTERFACE, (void *)&hCloseLuaInterface);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
