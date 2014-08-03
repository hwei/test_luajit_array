#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct
{
	size_t size;
	double *buffer;
} RawArray;

static int rawarray(lua_State *L)
{
	long size = luaL_checklong (L, 1);
	RawArray *p = lua_newuserdata(L, sizeof(RawArray));
	luaL_getmetatable(L, "rawarray");
	lua_setmetatable(L, -2);
	p->size = size;
	p->buffer = malloc(size * sizeof(double));
	if (p->buffer == NULL)
		luaL_error(L, "Can not malloc %d bytes.", size);
	return 1;
}

static int rawarray_index(lua_State *L)
{
	RawArray *p = (RawArray *)luaL_checkudata(L, 1, "rawarray");
	lua_Integer i = luaL_checkinteger (L, 2);
	if (i < 0 || i >= p->size)
		luaL_error (L, "Index out of range [0, %d).", p->size);
	lua_pushnumber (L, p->buffer[i]);
	return 1;
}

static int rawarray_newindex(lua_State *L)
{
	RawArray *p = (RawArray *)luaL_checkudata(L, 1, "rawarray");
	lua_Integer i = luaL_checkinteger (L, 2);
	lua_Number d = luaL_checknumber (L, 3);
	if (i < 0 || i >= p->size)
		luaL_error (L, "Index out of range [0, %d).", p->size);
	p->buffer[i] = d;
	return 0;
}

static int rawarray_gc(lua_State *L)
{
	RawArray *p = (RawArray *)luaL_checkudata(L, 1, "rawarray");
	free (p->buffer);
	return 0;
}

static const luaL_Reg rawarray_m[] = {
	{ "__index", rawarray_index },
	{ "__newindex", rawarray_newindex },
	{ "__gc", rawarray_gc },
	{ NULL, NULL }
};

static const luaL_Reg rawarray_lib[] = {
	{ "rawarray", rawarray },
	{ NULL, NULL }
};

LUALIB_API int luaopen_rawarray(lua_State *L)
{
	luaL_newmetatable(L, "rawarray");
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_settable(L, -3);
	luaL_register(L, NULL, rawarray_m);

	luaL_register(L, "rawarray", rawarray_lib);

	return 1;
}
