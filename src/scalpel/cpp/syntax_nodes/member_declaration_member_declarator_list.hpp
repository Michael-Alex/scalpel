/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_HPP

#include "member_declarator_list.hpp"
#include "decl_specifier_seq.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_declaration_member_declarator_list
	= !(member_declaration_decl_specifier_seq >> !s) >> !(member_declarator_list >> !s) >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		optional_node<decl_specifier_seq>,
		optional_node<member_declarator_list>,
		predefined_text_node<str::semicolon>
	>
	member_declaration_member_declarator_list
;

inline
const optional_node<decl_specifier_seq>&
get_decl_specifier_seq(const member_declaration_member_declarator_list& o)
{
	return get<0>(o);
}

inline
const optional_node<member_declarator_list>&
get_member_declarator_list(const member_declaration_member_declarator_list& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

