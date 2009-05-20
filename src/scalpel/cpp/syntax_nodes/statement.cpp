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

#include "statement_impl.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

statement::statement(labeled_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(expression_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(compound_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(selection_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(iteration_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(jump_statement&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(block_declaration&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(try_block&& o):
	impl_(new statement_impl(std::move(o)))
{
	add(*impl_);
}

statement::statement(const statement& o):
	composite_node(),
	impl_(new statement_impl(*o.impl_))
{
	add(*impl_);
}

statement::statement(statement&& o):
	composite_node(),
	impl_(new statement_impl(*o.impl_))
{
	add(*impl_);
}

statement::~statement()
{
	delete impl_;
}

const statement&
statement::operator=(const statement& o)
{
	impl_ = new statement_impl(*o.impl_);
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes
