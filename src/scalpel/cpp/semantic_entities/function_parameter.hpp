/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_PARAMETER_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_FUNCTION_PARAMETER_HPP

#include "type_variants_fwd.hpp"
#include <string>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class function_parameter
{
	public:
		function_parameter(const type_variant& t, const std::string& name);

		function_parameter(const function_parameter& o);

		function_parameter(function_parameter&& o);

		const function_parameter&
		operator=(const function_parameter& o);

		const function_parameter&
		operator=(function_parameter&& o);

		type_variant
		type() const;

		const std::string&
		name() const;

	private:
		weak_type_variant type_;
		std::string name_;
};

bool
operator==(const function_parameter& lhs, const function_parameter& rhs);

bool
operator!=(const function_parameter& lhs, const function_parameter& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

