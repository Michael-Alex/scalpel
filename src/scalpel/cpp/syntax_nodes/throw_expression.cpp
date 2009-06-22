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

#include "throw_expression.hpp"

#include "assignment_expression.hpp"
#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

throw_expression::throw_expression
(
	predefined_text_node<str::throw_>&& o0,
	optional_node<space>&& o1,
	optional_node<assignment_expression>&& o2
):
	impl_
	(
		new type
		(
			o0,
			o1,
			o2
		)
	)
{
	add(*impl_);
}

throw_expression::throw_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_
	(
		new type
		(
			head,
			tail
		)
	)
{
	add(*impl_);
}

throw_expression::throw_expression(const throw_expression& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

throw_expression::throw_expression(throw_expression&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

throw_expression::~throw_expression()
{
}

const throw_expression&
throw_expression::operator=(const throw_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

