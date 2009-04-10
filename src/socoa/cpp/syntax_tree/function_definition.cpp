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

#include "function_definition.hpp"

#include "declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

function_definition::function_definition
(
    boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
    declarator&& a_declarator,
    boost::optional<ctor_initializer>&& a_ctor_initializer
):
    decl_specifier_seq_(a_decl_specifier_seq),
    declarator_(std::make_shared<declarator>(std::move(a_declarator))),
    ctor_initializer_(a_ctor_initializer)
{
	update_node_list();
}

function_definition::function_definition(const function_definition& o):
	composite_node(),
    decl_specifier_seq_(o.decl_specifier_seq_),
    declarator_(o.declarator_),
    ctor_initializer_(o.ctor_initializer_)
{
	update_node_list();
}

function_definition::function_definition(function_definition&& o):
    decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
    declarator_(std::move(o.declarator_)),
    ctor_initializer_(std::move(o.ctor_initializer_))
{
	update_node_list();
}

const function_definition&
function_definition::operator=(const function_definition& o)
{
    decl_specifier_seq_ = o.decl_specifier_seq_;
    declarator_ = o.declarator_;
    ctor_initializer_ = o.ctor_initializer_;
	update_node_list();

	return *this;
}

void
function_definition::update_node_list()
{
	clear();
	if(decl_specifier_seq_) add(*decl_specifier_seq_);
	add(*declarator_);
	if(ctor_initializer_) add(*ctor_initializer_);
}

}}} //namespace socoa::cpp::syntax_tree
