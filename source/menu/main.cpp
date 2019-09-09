
typedef unsigned char uchar;

#include <interface.h>
#include <cdll_int.h>
#include <GarrysMod/Lua/Interface.h>

#include "luaInterface.h"
#include "conv.h"
#include "shared.h"

#include "vtable.h"

using namespace GarrysMod;

Lua::Shared* luaShared;

int CallOnClient(lua_State *state)
{
	const char *name = LUA->GetString(1);
	const char *data = LUA->GetString(2);

	Lua::Interface *CLIENT = luaShared->GetLuaInterface(0);

	if (!CLIENT)
		LUA->ThrowError("Not in game");

	CLIENT->PushSpecial(Lua::SPECIAL_GLOB);
	CLIENT->GetField(-1, "hook");
	CLIENT->GetField(-1, "Call");
	CLIENT->PushString(name, strlen(name));
	CLIENT->PushNil();
	CLIENT->PushString(data, strlen(data));
	CLIENT->Call(3, 1);
	CLIENT->Pop(3);

	return 0;
}

GMOD_MODULE_OPEN()
{
	luaShared = GetInterface<Lua::Shared*>("lua_shared", "LUASHARED003");

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
	LUA->PushString("CallOnClient");
	LUA->PushCFunction(CallOnClient);
	LUA->SetTable(-3);
	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
