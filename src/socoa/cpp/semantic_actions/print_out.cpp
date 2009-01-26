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

#include "print_out.h"

#include <iostream>
#include <string>

namespace socoa { namespace cpp { namespace semantic_actions
{

void
print_out(char const* first, char const* last)
{
    std::string str(first, last);
    std::cout << str << std::endl;
}

}}} //namespace socoa::cpp::semantic_actions
