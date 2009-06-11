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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPENAME_EXPRESION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPENAME_EXPRESION_HPP

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
typename_expression
	= str_p("typename") >> !s >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> identifier >> !s >> '(' >> !s >> !(expression >> !s) >> ')'
;
*/
class typename_expression: public composite_node
{
	public:
		typename_expression
		(
		);

		typename_expression(const typename_expression& o);

		typename_expression(typename_expression&& o);

		const typename_expression&
		operator=(const typename_expression& o);

	private:
		void
		update_node_list();
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
