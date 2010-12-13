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
#include <scalpel/utility/shared_ptr_variant.hpp>
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

 --------------------------------------------------------------
| Variadic | Variant | Multiple | Optional | result_type::type |
|----------|---------|----------|----------|-------------------|
|     0    |    0    |     0    |     X    |        (1)        |
|     0    |    0    |     1    |     X    |        (2)        |
|     0    |    1    |     0    |     0    |        (3)        |
|     0    |    1    |     0    |     1    |        (4)        |
|     0    |    1    |     1    |     X    |        (5)        |
|     1    |    0    |     0    |     0    |        (6)        |
|     1    |    0    |     0    |     1    |        (7)        |
|     1    |    0    |     1    |     X    |        (8)        |
|     1    |    1    |     X    |     X    |        (E)        |
 --------------------------------------------------------------

(1) std::shared_ptr<EntityT>
(2) std::set<(1)>
(3) utility::shared_ptr_variant<EntitiesT...>
(4) boost::optional<(3)>
(5) std::set<(3)>
(6) utility::shared_ptr_variant<EntitiesT...>
(7) boost::optional<(6)>
(8) std::set<(6)>
(E) Error
*/

template<bool Optional, bool Multiple, class... EntitiesT>
struct return_type;

//(1)
template<bool Optional, class EntityT>
struct return_type<Optional, false, EntityT>
{
	typedef std::shared_ptr<EntityT> type;
};

//(2)
template<bool Optional, class EntityT>
struct return_type<Optional, true, EntityT>
{
	typedef std::set<std::shared_ptr<EntityT>> type;
};

//(3)
template<class... EntitiesT>
struct return_type<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>
{
	typedef typename utility::shared_ptr_variant<EntitiesT...>::type type;
};

//(4)
template<class... EntitiesT>
struct return_type<true, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>
{
	typedef boost::optional<typename utility::shared_ptr_variant<EntitiesT...>::type> type;
};

//(5)
template<bool Optional, class... EntitiesT>
struct return_type<Optional, true, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>
{
	typedef std::set<typename utility::shared_ptr_variant<EntitiesT...>::type> type;
};

//(6)
template<class EntityT, class EntityT2, class... EntitiesT>
struct return_type<false, false, EntityT, EntityT2, EntitiesT...>
{
	typedef typename utility::shared_ptr_variant<EntityT, EntityT2, EntitiesT...>::type type;
};

//(7)
template<class EntityT, class EntityT2, class... EntitiesT>
struct return_type<true, false, EntityT, EntityT2, EntitiesT...>
{
	typedef boost::optional<typename utility::shared_ptr_variant<EntityT, EntityT2, EntitiesT...>::type> type;
};

//(8)
template<bool Optional, class EntityT, class EntityT2, class... EntitiesT>
struct return_type<Optional, true, EntityT, EntityT2, EntitiesT...>
{
	typedef std::set<typename utility::shared_ptr_variant<EntityT, EntityT2, EntitiesT...>::type> type;
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
template<bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const std::string& name,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part = true
);

/**
Find entities corresponding to the given identifier_or_template_id node,
from the given declarative region (unqualified name lookup).
*/
template<bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const std::string& name,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);

template<bool Optional, bool Multiple>
typename return_type<Optional, Multiple, semantic_entities::operator_function>::type
find_operator_functions
(
	const semantic_entities::overloadable_operator& op,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
);



namespace detail
{
	namespace identification_policies
	{
		struct by_name
		{
			typedef std::string identifier_t;

			template<class EntityT>
			static
			bool
			has_identifier(const EntityT& entity, const identifier_t& identifier)
			{
				return get_name(entity) == identifier;
			}
		};

		struct by_operator
		{
			typedef semantic_entities::overloadable_operator identifier_t;

			template<class EntityT>
			static
			bool
			has_identifier(const EntityT& entity, const identifier_t& identifier)
			{
				return entity->get_operator() == identifier;
			}
		};
	}



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
	template<class DeclarativeRegionT>
	typename return_type<false, false, DeclarativeRegionT>::type
	find_declarative_region
	(
		const bool has_leading_double_colon,
		const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
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
	typename return_type<false, false, DeclarativeRegionT>::type
	find_declarative_region
	(
		const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
		const typename return_type<false, false, DeclarativeRegionT>::type& current_declarative_region
	);

	/**
	Find entities corresponding to the given identifier,
	from the given declarative region (unqualified name lookup)
	*/
	template<class IdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_entities
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
	);



	/**
	Find entities corresponding to the given identifier,
	in the given namespace, applying using directives as defined in the
	qualified name lookup section of the C++ standard.
	*/
	template<class IdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_in_namespace
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		std::shared_ptr<semantic_entities::namespace_> current_namespace
	);

	/**
	Recursive part of above function.
	*/
	template<class IdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_in_namespace
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		std::shared_ptr<semantic_entities::namespace_> current_namespace,
		std::vector<std::shared_ptr<semantic_entities::namespace_>>& already_seached_namespaces
	);



	/**
	Find entities of the given identifier, in the given declarative region only.
	*/
	template<class IdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT, class EntityT2, class... EntitiesT>
	typename return_type<Optional, Multiple, EntityT, EntityT2, EntitiesT...>::type
	find_local_entities
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		const DeclarativeRegionT& current_declarative_region
	);

	template<class IdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT, class... EntitiesT>
	struct find_variadic_local_entities;

	template<class IdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT>
	struct find_variadic_local_entities<IdentificationPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT>
	{
		static
		void
		find
		(
			const typename IdentificationPolicy::identifier_t& identifier,
			const DeclarativeRegionT& current_declarative_region,
			ReturnT& found_entities
		);
	};

	template<class IdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT, class EntityT, class... EntitiesT>
	struct find_variadic_local_entities<IdentificationPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT, EntityT, EntitiesT...>
	{
		static
		void
		find
		(
			const typename IdentificationPolicy::identifier_t& identifier,
			const DeclarativeRegionT& current_declarative_region,
			ReturnT& found_entities
		);
	};

	/**
	Find entities of the given identifier, in the given declarative region only.
	*/
	template<class IdentificationPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT>
	typename return_type<Optional, Multiple, EntityT>::type
	find_local_entities
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		const DeclarativeRegionT& current_declarative_region
	);



	/**
	Find entities of the given identifier, in the given base classes
	*/
	template<class IdentificationPolicy, bool Optional, bool Multiple, class... EntitiesT>
	typename return_type<Optional, Multiple, EntitiesT...>::type
	find_entities_in_base_classes
	(
		const typename IdentificationPolicy::identifier_t& identifier,
		utility::shared_ptr_vector<semantic_entities::class_>::range base_classes
	);

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
	std::shared_ptr<semantic_entities::namespace_>
	find_common_enclosing_namespace
	(
		const semantic_entities::declarative_region_shared_ptr_variant& a,
		const std::shared_ptr<semantic_entities::namespace_> b
	);



	//result = entity
	template<class T, class U>
	inline
	void
	add_to_result(T& result, const U& entity);

	//add entity to result if entity isn't empty
	template<class T, class U>
	inline
	void
	add_to_result(std::set<T>& result, const U& entity);

	//add entity to result if entity isn't empty
	template<class T, class U>
	inline
	void
	add_to_result(std::set<T>& result, const boost::optional<U>& entity);

	//append entities to result
	template<class T, class U>
	inline
	void
	add_to_result(std::set<T>& result, const std::set<U>& entities);



	template<bool Optional, bool Multiple, class... EntitiesT>
	struct return_result;

	template<class... EntitiesT>
	struct return_result<true, false, EntitiesT...>
	{
		//return the only one element of the set
		//throw an exception if there's more than one element in the set
		static
		typename return_type<true, false, EntitiesT...>::type
		result(typename return_type<true, true, EntitiesT...>::type& result);

		//return result;
		static
		typename return_type<true, false, EntitiesT...>::type
		result(typename return_type<true, false, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, false, EntitiesT...>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, EntitiesT...>::type
		result(typename return_type<false, true, EntitiesT...>::type& result);

		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntitiesT...>::type
		result(typename return_type<true, false, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type
		result(typename return_type<false, true, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type
		result(typename return_type<true, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type& result);
	};

	template<class EntityT, class EntityT2, class... EntitiesT>
	struct return_result<false, false, EntityT, EntityT2, EntitiesT...>
	{
		//return the only one element of the set
		//throw an exception if there's zero or more than one element in
		//the set
		static
		typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
		result(typename return_type<false, true, EntityT, EntityT2, EntitiesT...>::type& result);

		//return *result;
		//throw an exception if the result is empty
		static
		typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
		result(typename return_type<true, false, EntityT, EntityT2, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<true, true, EntitiesT...>
	{
		//return result;
		static
		typename return_type<true, true, EntitiesT...>::type&
		result(typename return_type<true, true, EntitiesT...>::type& result);
	};

	template<class... EntitiesT>
	struct return_result<false, true, EntitiesT...>
	{
		//return result;
		//throw an exception if the result is empty
		static
		typename return_type<false, true, EntitiesT...>::type&
		result(typename return_type<true, true, EntitiesT...>::type& result);
	};
}

}}}}}} //namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis::name_lookup

#include "name_lookup.ipp"

#endif

