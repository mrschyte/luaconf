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

#include "luaconf.hpp"

/*
 * function version of the lua_tostring macro
 */
const char* lua_tocstring(lua_State* L, int index) {
    return lua_tolstring(L, index, NULL);
}

