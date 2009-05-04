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

#ifndef SOCOA_CPP_SYNTAX_NODES_EXCEPTION_DECLARATION_HPP
#define SOCOA_CPP_SYNTAX_NODES_EXCEPTION_DECLARATION_HPP

#include "../../util/extern_strings.hpp"
#include "alternative_node.hpp"
#include "simple_text_node.hpp"
#include "exception_declarator.hpp"
#include "exception_abstract_declarator.hpp"
#include "type_specifier_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		exception_declarator,
		exception_abstract_declarator,
		type_specifier_seq,
		simple_text_node<util::extern_strings::ellipsis>
	>
	exception_declaration
;

}}} //namespace socoa::cpp::syntax_nodes

#endif
