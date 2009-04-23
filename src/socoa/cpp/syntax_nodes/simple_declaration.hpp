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

#ifndef SOCOA_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "init_declarator_list.hpp"
#include "decl_specifier_seq.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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
			boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
			boost::optional<space>&& post_decl_specifier_seq_space_node,
			boost::optional<init_declarator_list>&& an_init_declarator_list,
			boost::optional<space>&& post_init_declarator_list_space_node
		);

		simple_declaration(const simple_declaration& o);

		simple_declaration(simple_declaration&& o);

		const simple_declaration&
		operator=(const simple_declaration& o);

		inline
		const boost::optional<const decl_specifier_seq&>
		get_decl_specifier_seq() const;

		inline
		const boost::optional<const init_declarator_list&>
		get_init_declarator_list() const;

	private:
		void
		update_node_list();

		boost::optional<decl_specifier_seq> decl_specifier_seq_;
		boost::optional<space> post_decl_specifier_seq_space_;
		boost::optional<init_declarator_list> init_declarator_list_;
		boost::optional<space> post_init_declarator_list_space_;
};

inline
const boost::optional<const decl_specifier_seq&>
simple_declaration::get_decl_specifier_seq() const
{
	return boost::optional<const decl_specifier_seq&>(decl_specifier_seq_);
}

inline
const boost::optional<const init_declarator_list&>
simple_declaration::get_init_declarator_list() const
{
	return boost::optional<const init_declarator_list&>(init_declarator_list_);
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
