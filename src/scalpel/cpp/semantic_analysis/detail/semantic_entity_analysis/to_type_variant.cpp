/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#include "to_type_variant.hpp"
#include <scalpel/utility/variant/apply_visitor.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace semantic_entity_analysis
{

using namespace semantic_entities;

namespace
{
	struct: public utility::static_visitor<type_variant>
	{
		template<class T>
		type_variant
		operator()(T* t) const
		{
			return type_variant(static_cast<const T*>(t));
		}

		type_variant
		operator()(typedef_* t) const
		{
			return t->type();
		}

		type_variant
		operator()(member_typedef* t) const
		{
			return t->type();
		}
	} to_type_variant_impl;
}

semantic_entities::type_variant
to_type_variant
(
	const typename utility::ptr_variant
	<
		semantic_entities::class_,
		semantic_entities::member_class,
		semantic_entities::typedef_,
		semantic_entities::member_typedef,
		semantic_entities::enum_,
		semantic_entities::member_enum
	>::type& var
)
{
	return utility::apply_visitor(to_type_variant_impl, var);
}

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis

