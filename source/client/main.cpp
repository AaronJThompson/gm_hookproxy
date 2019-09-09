
typedef unsigned char uchar;

#include <interface.h>
#include <cdll_int.h>
#include <GarrysMod/Lua/Interface.h>

#include <string>

#include "luaInterface.h"
#include "conv.h"
#include "shared.h"

#include "vtable.h"

using namespace GarrysMod;

Lua::Shared* luaShared;

int CallOnMenu(lua_State *state)
{
	Lua::Interface *CLIENT = luaShared->GetLuaInterface(0);
	Lua::Interface *MENU = luaShared->GetLuaInterface(2);

	if (!MENU)
		LUA->ThrowError("Can't get menu");

	const char *name = LUA->GetString(1);
	ILuaObject *data = CLIENT->GetObject(2);

	MENU->PushSpecial(Lua::SPECIAL_GLOB);
	MENU->GetField(-1, "hook");
	MENU->GetField(-1, "Call");
	MENU->PushString(name, strlen(name));
	MENU->PushNil();
	MENU->PushLuaObject(data);
	MENU->Call(3, 1);
	MENU->Pop(3);

	return 0;
}

GMOD_MODULE_OPEN()
{
	luaShared = GetInterface<Lua::Shared*>("lua_shared", "LUASHARED003");

	LUA->PushSpecial(Lua::SPECIAL_GLOB);
		LUA->PushString("CallOnMenu");
		LUA->PushCFunction(CallOnMenu);
		LUA->SetTable(-3);
	LUA->Pop();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	return 0;
}
