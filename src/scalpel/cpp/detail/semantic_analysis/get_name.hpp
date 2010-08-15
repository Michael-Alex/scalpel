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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_GET_NAME_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_GET_NAME_HPP

#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class EntityT>
const std::string&
get_name(EntityT entity);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

