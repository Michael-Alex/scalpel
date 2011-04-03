/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "leaf_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

leaf_node::leaf_node()
{
}

leaf_node::leaf_node(const std::string& value):
	value_(value)
{
}

leaf_node::leaf_node(std::string&& value):
	value_(std::move(value))
{
}

leaf_node::leaf_node(const leaf_node& n):
	value_(n.value_)
{
}

leaf_node::leaf_node(leaf_node&& n):
	value_(std::move(n.value_))
{
}

const std::string&
leaf_node::value() const
{
	return value_;
}

void
leaf_node::value(const std::string& code)
{
	value_ = code;
}

void
leaf_node::value(std::string&& code)
{
	value_ = std::move(code);
}

}}} //namespace scalpel::cpp::syntax_nodes

