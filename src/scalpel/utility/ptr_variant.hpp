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

#ifndef SCALPEL_UTILITY_PTR_VARIANT_HPP
#define SCALPEL_UTILITY_PTR_VARIANT_HPP

#include "variant.hpp"
#include "apply_type_trait_to_variadic_template_parameters.hpp"
#include <boost/type_traits/add_pointer.hpp>

namespace scalpel { namespace utility
{

template<typename... Ts>
struct ptr_variant
{
	typedef typename apply_type_trait_to_variadic_template_parameters<boost::add_pointer, variant, Ts...>::type type;
};

}} //namespace scalpel::utility

#endif

