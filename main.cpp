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

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "luaconf.hpp"

void process_config(lua_State* L) {
    printf("float_value: %f\n", lua_evalexpr(L, lua_tonumber, "luaconf.config.float_value"));
    printf("integer_value: %d\n", lua_evalexpr(L, lua_tointeger, "luaconf.config.integer_value"));
    printf("string_value: %s\n", lua_evalexpr(L, lua_tocstring, "luaconf.config.string_value"));
    
    int length = lua_evalexpr(L, lua_tointeger, "#luaconf.config.integer_array");
    printf("integer_array:\n");

    for (int i = 0; i < length; i++) {
        printf("  %d\n", lua_evalexpr(L, lua_tointeger, "luaconf.config.integer_array[%d]", i + 1));
    }
}


int main(int argc, char** argv) {

    if (argc > 1) {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        luaopen_luaconf(L);

        if (luaL_dofile(L, argv[1]) != 0) {
            printf("couldn't parse file: %s\n", argv[1]);
        }

        process_config(L);
        lua_close(L);
    }

    return 0;
}
