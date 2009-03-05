/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "built_in_type_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

const std::vector<std::string> built_in_type_specifier_string_list
{
    "char",
    "wchar_t",
    "bool",
    "short",
    "int",
    "long",
    "signed",
    "unsigned",
    "float",
    "double",
    "void"
};

}}} //namespace socoa::cpp::syntax_tree
