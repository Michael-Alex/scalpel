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

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/is_empty.hpp>
#include <scalpel/utility/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <set>
#include <vector>
#include <memory>
#include <sstream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace semantic_graph_analysis { namespace name_lookup
{

/*
result_type's truth table:

| Variadic | Variant | Multiple | Optional | result_type::type
|----------|---------|----------|----------|------------------
|     0    |    0    |     0    |     X    |        (1)
|     0    |    0    |     1    |     X    |        (2)
|     0    |    1    |     0    |     0    |        (3)
|     0    |    1    |     0    |     1    |        (4)
|     0    |    1    |     1    |     X    |        (5)
|     1    |    0    |     0    |     0    |        (6)
|     1    |    0    |     0    |     1    |        (7)
|     1    |    0    |     1    |     X    |        (8)
|     1    |    1    |     X    |     X    |        (E)

(1) std::shared_ptr<EntityT>
(2) std::set<(1)>
(3) utility::variant<EntitiesT...>
(4) boost::optional<(3)>
(5) std::set<(3)>
(E) Error
*/

template<bool Optional, bool Multiple, class EntityT>
struct return_type;

template<bool Optional, class EntityT>
struct return_type<Optional, false, EntityT>
{
	typedef std::shared_ptr<EntityT> type;
};

template<class... EntitiesT>
struct return_type<true, false, utility::variant<EntitiesT...>>
{
	typedef boost::optional<utility::variant<EntitiesT...>> type;
};

template<class... EntitiesT>
struct return_type<false, false, utility::variant<EntitiesT...>>
{
	typedef utility::variant<EntitiesT...> type;
};

template<bool Optional, class EntityT>
struct return_type<Optional, true, EntityT>
{
	typedef std::set<std::shared_ptr<EntityT>> type;
};

template<bool Optional, class... EntitiesT>
struct return_type<Optional, true, utility::variant<EntitiesT...>>
{
	typedef std::set<utility::variant<EntitiesT...>> type;
};



/**
Find entities corresponding to the given nested identifier
(or nested template-id),
from the given declarative region (qualified name lookup).
apply_using_directives_for_unqualified_id_part determines whether the name
lookup of the unqualified-id part of the given nested identifier must apply
using directives. It must be set to false when looking up the declaration of a
function we're going to define.
*/
template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part = true
);

/**
Find entities corresponding to the given identifier_or_template_id node,
from the given declarative region (unqualified name lookup).
*/
template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);



class impl
{
	template<bool Optional, bool Multiple, class EntityT>
	friend
	typename return_type<Optional, Multiple, EntityT>::type
	find
	(
		const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
		const bool apply_using_directives_for_unqualified_id_part = true
	);

	template<bool Optional, bool Multiple, class EntityT>
	friend
	typename return_type<Optional, Multiple, EntityT>::type
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
	typename return_type<false, false, DeclarativeRegionT>::type
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
	typename return_type<false, false, DeclarativeRegionT>::type
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const typename return_type<false, false, DeclarativeRegionT>::type& current_declarative_region
	);

	/**
	Find entities corresponding to the given name,
	from the given declarative region (unqualified name lookup)
	*/
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
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
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_in_namespace
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		std::shared_ptr<semantic_entities::namespace_> current_namespace
	);

	/**
	Find in namespace from an identifier.
	*/
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_in_namespace_from_identifier
	(
		const std::string& name,
		std::shared_ptr<semantic_entities::namespace_> current_namespace,
		std::vector<std::shared_ptr<semantic_entities::namespace_>>& already_seached_namespaces
	);



	/**
	Find entities corresponding to the given identifier_or_template_id node,
	in the given declarative region only.
	*/
	template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_local_entities
	(
		const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
		const DeclarativeRegionT& current_declarative_region
	);

	/**
	Find entities of the given name, in the given declarative region only.
	*/
	template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_local_entities_from_identifier
	(
		const std::string& name,
		const DeclarativeRegionT& current_declarative_region
	);



	/**
	Find entities of the given name, in the given base classes
	*/
	template<bool Optional, bool Multiple, class EntityT>
	static
	typename return_type<Optional, Multiple, EntityT>::type
	find_entities_in_base_classes
	(
		const std::string& name,
		utility::shared_ptr_vector<semantic_entities::class_>::range base_classes
	);

	static
	void
	apply_using_directives
	(
		const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
		const std::vector<std::weak_ptr<semantic_entities::namespace_>>& using_directive_namespaces,
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
	add_to_result(std::set<T>& result, const U& entity);

	//add entity to result if entity isn't empty
	template<class T, class U>
	inline
	static
	void
	add_to_result(std::set<T>& result, const boost::optional<U>& entity);

	//append entities to result
	template<class T, class U>
	inline
	static
	void
	add_to_result(std::set<T>& result, const std::set<U>& entities);



	template<bool Optional, bool Multiple, class EntityT>
	struct return_result;

	template<class EntityT>
	struct return_result<true, false, EntityT>
	{
		//return the only one element of the set
		//throw an exception if there's more than one element in the set
		static
		typename return_type<true, false, EntityT>::type
		result(typename return_type<true, true, EntityT>::type& result);

		//return result;
		static
		typename return_type<true, false, EntityT>::type
		result(typename return_type<true, false, EntityT>::type& result);
	};

	template<class EntityT>
	struct return_result<false, false, EntityT>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, EntityT>::type
		result(typename return_type<false, true, EntityT>::type& result);

		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntityT>::type
		result(typename return_type<true, false, EntityT>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, false, utility::variant<EntitiesT...>>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, utility::variant<EntitiesT...>>::type
		result(typename return_type<false, true, utility::variant<EntitiesT...>>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, utility::variant<EntitiesT...>>::type
		result(typename return_type<true, false, utility::variant<EntitiesT...>>::type& result);
	};

	template<class EntityT>
	struct return_result<true, true, EntityT>
	{
		//return result;
		static
		std::set<std::shared_ptr<EntityT>>&
		result(std::set<std::shared_ptr<EntityT>>& result);
	};

	template<class EntityT>
	struct return_result<false, true, EntityT>
	{
		//return result;
		//throw an exception if the result is empty
		static
		std::set<std::shared_ptr<EntityT>>&
		result(std::set<std::shared_ptr<EntityT>>& result);
	};
};

}}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis::name_lookup

#include "name_lookup.ipp"

#endif

