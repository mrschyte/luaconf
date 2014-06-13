/*
 *  This file is part of luaconf, the lua based configuration library.
 *  Copyright (C) 2009   Peter Kasza
 *
 *  luaconf is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  luaconf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with luaconf.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LUACONFIG_HPP__
#define __LUACONFIG_HPP__

// default size of the format string buffer on stack
#define LUA_EVAL_FMT_BUFSIZ     512

extern "C" {
#include <stdlib.h>
#include <lauxlib.h>
#include <lualib.h>
#include <lua.h>
}

#include <exception>

extern "C" int luaopen_luaconf(lua_State* L);
const char* lua_tocstring(lua_State* L, int index);

class luaexception: public std::exception {
private:
    const char* error;

public:
    luaexception(const char* error) {
        this->error = error;
    }

public:
    virtual const char* what() const throw() {
        return error;
    }
};

/*
 * This function evaluates a lua expression and returns its value
 * converted by the callback function.
 *
 * Parameters:
 *      L      -- the actual lua state
 *      cb     -- callback function for converting the returned value
 *                lua provides the following builtin functions for this
 *                  lua_tointeger
 *                  lua_tonumber
 *                  lua_tostring (macro), use lua_tocstring instead
 *      fmt   -- is a printf style format string
 *      ...   -- vararg parameters for the function
 */
template <typename T>
T lua_evalexpr(lua_State* L, T (*cb)(lua_State*, int), const char* fmt, ...) {
    char buffer[LUA_EVAL_FMT_BUFSIZ];
    char* s = &buffer[0];
    va_list args;
    int n;

    T res;

    va_start(args, fmt);
    n = vsnprintf(buffer, LUA_EVAL_FMT_BUFSIZ, fmt, args);
    if (n >= LUA_EVAL_FMT_BUFSIZ) { // vsnprintf need more space, allocate using malloc
        s = (char*) malloc(n);
        n = vsnprintf(buffer, LUA_EVAL_FMT_BUFSIZ, fmt, args);
    }
    va_end(args);

    lua_getfield(L, LUA_GLOBALSINDEX, "luaconf");
	lua_pushstring(L, "eval"); // retrieve luaconf.eval
	lua_gettable(L, -2);

    lua_pushstring(L, s);
    lua_call(L, 1, 1); // call luaconf.eval(s)

    if (s != &buffer[0]) // free the buffer if we allocated it
        free(s);
    
    // if return value is nil, throw exception
    if (lua_isnil(L, -1)) throw luaexception("value is nil");

    // get result and transform it to type T
    res = cb(L, -1);
    lua_pop(L, 1); // clear stack

    return res;
}

#endif

