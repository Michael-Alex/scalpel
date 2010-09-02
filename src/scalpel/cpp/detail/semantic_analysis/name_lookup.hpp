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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_HPP

#include "get_members.hpp"
#include "get_name.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/is_empty.hpp>
#include <scalpel/utility/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

template<class EntityT, bool Optional, bool Multiple>
struct return_type;

template<class EntityT, bool Optional>
struct return_type<EntityT, Optional, false>
{
	typedef std::shared_ptr<EntityT> type;
};

template<class... EntitiesT>
struct return_type<utility::variant<EntitiesT...>, true, false>
{
	typedef boost::optional<utility::variant<EntitiesT...>> type;
};

template<class... EntitiesT>
struct return_type<utility::variant<EntitiesT...>, false, false>
{
	typedef utility::variant<EntitiesT...> type;
};

template<class EntityT, bool Optional>
struct return_type<EntityT, Optional, true>
{
	typedef std::vector<std::shared_ptr<EntityT>> type;
};

template<class... EntitiesT, bool Optional>
struct return_type<utility::variant<EntitiesT...>, Optional, true>
{
	typedef std::vector<utility::variant<EntitiesT...>> type;
};



/**
Find entities corresponding to the given nested identifier
(or nested template-id),
from the given declarative region (qualified name lookup).
*/
template<class EntityT, bool Optional, bool Multiple>
typename return_type<EntityT, Optional, Multiple>::type
find
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);

/**
Find entities corresponding to the given identifier_or_template_id node,
from the given declarative region (unqualified name lookup).
*/
template<class EntityT, bool Optional, bool Multiple>
typename return_type<EntityT, Optional, Multiple>::type
find
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);



class impl
{
	template<class EntityT, bool Optional, bool Multiple>
	friend
	typename return_type<EntityT, Optional, Multiple>::type
	find
	(
		const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	template<class EntityT, bool Optional, bool Multiple>
	friend
	typename return_type<EntityT, Optional, Multiple>::type
	find
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	//used for applying using directives
	typedef
		std::map
		<
			std::shared_ptr<const semantic_entities::namespace_>,
			std::vector<std::shared_ptr<semantic_entities::namespace_>>
		>
		namespace_association_map
	;

	/**
	Find the declarative region corresponding to the given
	nested-identifier-or-template-id syntax node
	(i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region.
	DeclarativeRegionT determines both the return type and the type of the
	intermediate declarative region(s) (X and Y in the example).
	*/
	//TODO nested_identifier_or_template_id provides too much information.
	//A syntax node type containing an optional '::' and a nested-name-specifier
	//would have been more appropriate.
	template<class DeclarativeRegionT>
	static
	typename return_type<DeclarativeRegionT, false, false>::type
	find_declarative_region
	(
		const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
	);

	/**
	Find the declarative region corresponding to the given nested-name-specifier
	syntax node (i.e. Z in the expression "X::Y::Z::"),
	from the given declarative region (where X must be declared).
	DeclarativeRegionT determines both the return type and the type of the
	intermediate declarative region(s) (X and Y in the example).
	*/
	template<class DeclarativeRegionT>
	static
	typename return_type<DeclarativeRegionT, false, false>::type
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const typename return_type<DeclarativeRegionT, false, false>::type& current_declarative_region
	);

	/**
	Find entities corresponding to the given name,
	from the given declarative region (unqualified name lookup)
	*/
	template<class EntityT, bool Optional, bool Multiple>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_entities_from_identifier
	(
		const std::string& name,
		semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
	);



	/**
	Find entities corresponding to the given identifier_or_template_id node,
	in the given namespace, applying using directives as defined in the
	qualified name lookup section of the C++ standard.
	*/
	template<class EntityT, bool Optional, bool Multiple>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_in_namespace
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		std::shared_ptr<semantic_entities::namespace_> current_namespace
	);

	/**
	Find in namespace from an identifier.
	*/
	template<class EntityT, bool Optional, bool Multiple>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_in_namespace_from_identifier
	(
		const std::string& name,
		std::shared_ptr<semantic_entities::namespace_> current_namespace
	);



	/**
	Find entities corresponding to the given identifier_or_template_id node,
	in the given declarative region only.
	*/
	template<class EntityT, bool Optional, bool Multiple, class DeclarativeRegionT>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_local_entities
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		DeclarativeRegionT& current_declarative_region
	);

	/**
	Find entities of the given name, in the given declarative region only.
	*/
	template<class EntityT, bool Optional, bool Multiple, class DeclarativeRegionT>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_local_entities_from_identifier
	(
		const std::string& name,
		DeclarativeRegionT& current_declarative_region
	);



	/**
	Find entities of the given name, in the given base classes
	*/
	template<class EntityT, bool Optional, bool Multiple>
	static
	typename return_type<EntityT, Optional, Multiple>::type
	find_entities_in_base_classes
	(
		const std::string& name,
		utility::vector<std::shared_ptr<semantic_entities::class_>>::range base_classes
	);

	static
	void
	apply_using_directives
	(
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
		const utility::vector<std::weak_ptr<semantic_entities::namespace_>>& using_directive_namespaces,
		namespace_association_map& namespace_associations
	);

	/**
	Find the nearest enclosing namespace containing both a and b.
	*/
	static
	std::shared_ptr<semantic_entities::namespace_>
	find_common_enclosing_namespace
	(
		const semantic_entities::declarative_region_shared_ptr_variant& a,
		const std::shared_ptr<semantic_entities::namespace_> b
	);

	//result = entity
	template<class T, class U>
	inline
	static
	void
	add_to_result(T& result, const U& entity);

	//add entity to result if entity isn't empty
	template<class T, class U>
	inline
	static
	void
	add_to_result(std::vector<T>& result, const U& entity);

	//add entity to result if entity isn't empty
	template<class T, class U>
	inline
	static
	void
	add_to_result(std::vector<T>& result, const boost::optional<U>& entity);

	//append entities to result
	template<class T, class U>
	inline
	static
	void
	add_to_result(std::vector<T>& result, const std::vector<U>& entities);



	template<class EntityT, bool Optional, bool Multiple>
	struct return_result;

	template<class EntityT>
	struct return_result<EntityT, true, false>
	{
		//return the only one element of the vector
		//throw an exception if there's more than one element in the vector
		static
		typename return_type<EntityT, true, false>::type
		result(typename return_type<EntityT, true, true>::type& result);

		//return result;
		static
		typename return_type<EntityT, true, false>::type
		result(typename return_type<EntityT, true, false>::type& result);
	};

	template<class EntityT>
	struct return_result<EntityT, false, false>
	{
		//return the only one element of the vector
		//throw an exception if there's zero or more than one element in
		//the vector
		static
		typename return_type<EntityT, false, false>::type
		result(typename return_type<EntityT, false, true>::type& result);

		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<EntityT, false, false>::type
		result(typename return_type<EntityT, true, false>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<utility::variant<EntitiesT...>, false, false>
	{
		//return the only one element of the vector
		//throw an exception if there's zero or more than one element in
		//the vector
		static
		typename return_type<utility::variant<EntitiesT...>, false, false>::type
		result(typename return_type<utility::variant<EntitiesT...>, false, true>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<utility::variant<EntitiesT...>, false, false>::type
		result(typename return_type<utility::variant<EntitiesT...>, true, false>::type& result);
	};

	template<class EntityT>
	struct return_result<EntityT, true, true>
	{
		//return result;
		static
		std::vector<std::shared_ptr<EntityT>>&
		result(std::vector<std::shared_ptr<EntityT>>& result);
	};

	template<class EntityT>
	struct return_result<EntityT, false, true>
	{
		//return result;
		//throw an exception if the result is empty
		static
		std::vector<std::shared_ptr<EntityT>>&
		result(std::vector<std::shared_ptr<EntityT>>& result);
	};
};

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

#include "name_lookup.ipp"

#endif

