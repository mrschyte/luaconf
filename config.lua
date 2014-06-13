--[[
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
]]--

--[[
   these values override the defaults defined
   in the swig interface file "luaconf.i"
]]--

luaconf.setconfig({
    float_value     = 2.71,
    integer_value   = 1024,
    integer_array   = { 2, 3, 5, 7 }
});
