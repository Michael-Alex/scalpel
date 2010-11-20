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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_GET_MEMBERS_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_GET_MEMBERS_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/vector.hpp>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

template<class EntityT>
struct get_members_type_traits;

template<>
struct get_members_type_traits<semantic_entities::open_declarative_region_shared_ptr_variant>
{
	typedef utility::vector<semantic_entities::open_declarative_region_shared_ptr_variant> return_type;
};

template<>
struct get_members_type_traits<semantic_entities::namespace_>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::namespace_>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::class_>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::class_>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::simple_function>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::simple_function>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::operator_function>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::operator_function>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::statement_block>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::statement_block>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::variable>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::variable>>::range return_type;
};

template<>
struct get_members_type_traits<semantic_entities::namespace_alias>
{
	typedef utility::vector<std::shared_ptr<semantic_entities::namespace_alias>>::range return_type;
};


template<class MemberT, class ParentT>
typename get_members_type_traits<MemberT>::return_type
get_members(ParentT parent);

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#endif

