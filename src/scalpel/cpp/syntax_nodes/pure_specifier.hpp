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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PURE_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PURE_SPECIFIER_HPP

#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
pure_specifier
	= ch_p('=') >> !s >> '0'
;
*/
typedef
	sequence_node
	<
		simple_text_node<str::equal>,
		optional_node<space>,
		simple_text_node<str::zero>
	>
	pure_specifier
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif