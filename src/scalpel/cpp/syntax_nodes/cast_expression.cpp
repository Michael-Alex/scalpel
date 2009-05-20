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

#include "cast_expression.hpp"

#include "cast_expression_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

cast_expression::cast_expression
(
	unary_expression&& unary_expression_node
):
	impl_(new cast_expression_impl(std::move(unary_expression_node)))
{
	add(*impl_);
}

cast_expression::cast_expression(const cast_expression& o):
	composite_node(),
	impl_(new cast_expression_impl(*o.impl_))
{
	add(*impl_);
}

cast_expression::cast_expression(cast_expression&& o):
	composite_node(),
	impl_(new cast_expression_impl(std::move(*o.impl_)))
{
	add(*impl_);
}

cast_expression::~cast_expression()
{
	delete impl_;
}

const cast_expression&
cast_expression::operator=(const cast_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

