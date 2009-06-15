/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "function_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

function_definition::function_definition(simple_function_definition&& o):
	impl_(o)
{
	add(impl_);
}

function_definition::function_definition(try_block_function_definition&& o):
	impl_(o)
{
	add(impl_);
}

function_definition::function_definition(const function_definition& o):
	impl_(o.impl_)
{
	add(impl_);
}

function_definition::function_definition(function_definition&& o):
	impl_(o.impl_)
{
	add(impl_);
}

const function_definition&
function_definition::operator=(const function_definition& o)
{
	impl_ = o.impl_;
	return *this;
}

void
function_definition::get(boost::optional<const simple_function_definition&>& o) const
{
	impl_.get(o);
}

void
function_definition::get(boost::optional<const try_block_function_definition&>& o) const
{
	impl_.get(o);
}



const declarator&
get_declarator(const function_definition& o)
{
	if(auto def = get<simple_function_definition>(&o))
	{
		return get<2>(*def);
	}
	else
	{
		auto def = get<try_block_function_definition>(&o);
		return get<2>(*def);
	}
}

}}} //namespace scalpel::cpp::syntax_nodes

