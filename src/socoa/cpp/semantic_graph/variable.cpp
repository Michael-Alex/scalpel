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

#include "variable.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

variable::variable(std::string&& name):
	name_(std::move(name))
{
}

variable::variable(variable&& v):
	name_(std::move(v.name_))
{
}

const variable&
variable::operator=(variable&& v)
{
	name_ = std::move(v.name_);

	return *this;
}

const std::string&
variable::get_name() const
{
	return name_;
}

}}} //namespace socoa::cpp::semantic_graph

