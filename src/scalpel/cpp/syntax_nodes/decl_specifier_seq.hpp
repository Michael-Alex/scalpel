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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECL_SPECIFIER_SEQ_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECL_SPECIFIER_SEQ_HPP

#include "decl_specifier.hpp"
#include "list_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	list_node<decl_specifier>
   	decl_specifier_seq
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif

