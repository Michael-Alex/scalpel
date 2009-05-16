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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "init_declarator_list.hpp"
#include "decl_specifier_seq.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
simple_declaration
	= [decl_specifier_seq], [init_declarator_list], ";"
;
\endverbatim
*/
class simple_declaration: public composite_node
{
	public:
		simple_declaration
		(
			optional_node<decl_specifier_seq>&& a_decl_specifier_seq,
			optional_node<space>&& post_decl_specifier_seq_space_node,
			optional_node<init_declarator_list>&& an_init_declarator_list,
			optional_node<space>&& post_init_declarator_list_space_node
		);

		simple_declaration(const simple_declaration& o);

		simple_declaration(simple_declaration&& o);

		const simple_declaration&
		operator=(const simple_declaration& o);

		inline
		const optional_node<decl_specifier_seq>&
		decl_specifier_seq_node() const;

		inline
		const optional_node<init_declarator_list>&
		init_declarator_list_node() const;

	private:
		void
		update_node_list();

		optional_node<decl_specifier_seq> decl_specifier_seq_;
		optional_node<space> post_decl_specifier_seq_space_;
		optional_node<init_declarator_list> init_declarator_list_;
		optional_node<space> post_init_declarator_list_space_;
};

inline
const optional_node<decl_specifier_seq>&
simple_declaration::decl_specifier_seq_node() const
{
	return decl_specifier_seq_;
}

inline
const optional_node<init_declarator_list>&
simple_declaration::init_declarator_list_node() const
{
	return init_declarator_list_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
