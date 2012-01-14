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

#include "expression_construction.hpp"
#include "value_construction.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

semantic_entities::expression_t
create_expression_from_literal(const syntax_nodes::literal& literal_node)
{
	if(const boost::optional<const integer_literal&>& opt_integer_literal_node = get<integer_literal>(&literal_node))
		return create_integer_value(*opt_integer_literal_node);
	if(const boost::optional<const boolean_literal&>& opt_boolean_literal_node = get<boolean_literal>(&literal_node))
		return create_boolean_value(*opt_boolean_literal_node);
	if(const boost::optional<const floating_literal&>& opt_floating_literal_node = get<floating_literal>(&literal_node))
		return create_floating_value(*opt_floating_literal_node);
	if(const boost::optional<const character_literal&>& opt_character_literal_node = get<character_literal>(&literal_node))
		return create_character_value(*opt_character_literal_node);
	if(const boost::optional<const string_literal&>& opt_string_literal_node = get<string_literal>(&literal_node))
		return create_string_value(*opt_string_literal_node);

	assert(false);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

