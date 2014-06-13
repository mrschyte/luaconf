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

%module luaconf

%{
#include "luaconf.hpp"
%}

/*
 * Use swig expressions here to define constants from header files, etc.
 */

%luacode {
    -- default configuration values can be overridden by the configuration file
    luaconf.config = {
        integer_array              = { 1, 2, 3 },
        integer_value              = 121,
        float_value                = 3.14,
        string_value               = "Anne, I vote more cars race Rome to Vienna."
    }

    function luaconf.setconfig(c) do
            for k, v in pairs(c) do
                if not (luaconf.config[k] == nil) then
                    luaconf.config[k] = v
                else
                    print("invalid key: " .. k)
                end
            end
        end
    end

    function luaconf.eval(s)
        return assert(loadstring("return " .. s))();
    end
}
