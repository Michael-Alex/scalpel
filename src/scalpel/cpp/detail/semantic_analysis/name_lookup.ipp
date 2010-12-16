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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP_IPP

#include "semantic_entity_analysis/get_global_namespace.hpp"
#include "semantic_entity_analysis/get_name.hpp"
#include "semantic_entity_analysis/get_members.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup
{

template<class IdentifierGettingPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	using namespace detail;

	//used for applying using directives
	namespace_association_map namespace_associations;

	//indirectly returned object
	typename return_type<true, true, EntitiesT...>::type found_entities;

	//find entities from current to outermost declarative region
	//(i.e. the global namespace)
	while(true)
	{
		//apply using directives (only for namespaces and statement blocks)
		if(auto opt_namespace_ptr = utility::get<semantic_entities::namespace_>(&current_declarative_region))
			apply_using_directives
			(
				current_declarative_region,
				(*opt_namespace_ptr)->using_directive_namespaces(),
				namespace_associations
			);
		else if(auto opt_statement_block_ptr = utility::get<semantic_entities::statement_block>(&current_declarative_region))
			apply_using_directives
			(
				current_declarative_region,
				(*opt_statement_block_ptr)->using_directive_namespaces(),
				namespace_associations
			);

		//find entities in this declarative region only
		add_to_result
		(
			found_entities,
			find_local_entities
			<
				IdentifierGettingPolicy,
				semantic_entities::declarative_region_shared_ptr_variant,
				true,
				Multiple,
				EntitiesT...
			>(identifier, current_declarative_region)
		);

		//find entities in the associated namespaces (only for namespaces)
		//and add them to the previously found entities
		if(auto opt_namespace_ptr = utility::get<semantic_entities::namespace_>(&current_declarative_region))
		{
			auto associated_namespaces_it = namespace_associations.find(*opt_namespace_ptr);
			if(associated_namespaces_it != namespace_associations.end())
			{
				const std::vector<std::shared_ptr<semantic_entities::namespace_>>& associated_namespaces = associated_namespaces_it->second;

				//for each associated namespace
				for(auto i = associated_namespaces.begin(); i != associated_namespaces.end(); ++i)
				{
					add_to_result
					(
						found_entities,
						find_local_entities
						<
							IdentifierGettingPolicy,
							std::shared_ptr<semantic_entities::namespace_>,
							true,
							Multiple,
							EntitiesT...
						>(identifier, *i)
					);
				}
			}
		}

		//stop lookup if entities have been found
		if(!utility::is_empty(found_entities)) break;

		//find entities in the base classes (only for classes)
		if(auto opt_class_ptr = utility::get<semantic_entities::class_>(&current_declarative_region))
		{
			std::shared_ptr<semantic_entities::class_> class_ptr = *opt_class_ptr;

			add_to_result
			(
				found_entities,
				find_entities_in_base_classes
				<
					IdentifierGettingPolicy,
					true,
					Multiple,
					EntitiesT...
				>(identifier, class_ptr->base_classes())
			);

			//stop lookup if entities have been found
			if(!utility::is_empty(found_entities)) break;
		}

		//iterate to the enclosing declarative region
		if(!has_enclosing_declarative_region(current_declarative_region)) break;
		current_declarative_region = get_enclosing_declarative_region(current_declarative_region);
	}

	return std::move(return_result<Optional, Multiple, EntitiesT...>::result(found_entities));
}

template<class IdentifierGettingPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region,
	const bool apply_using_directives_for_unqualified_id_part
)
{
	using namespace detail;

	//Check whether the given qualified identifier is really qualified.
	//If not, perform a simple unqualified identifier lookup.
	if
	(
		!has_leading_double_colon &&
		!opt_nested_name_specifier_node
	)
	{
		return
			find
			<
				IdentifierGettingPolicy,
				Optional,
				Multiple,
				EntitiesT...
			>(identifier, current_declarative_region)
		;
	}

	//Find the last declarative region of the nested identifier specifier
	//(i.e. Z in "[::]X::Y::Z::").
	semantic_entities::open_declarative_region_shared_ptr_variant last_declarative_region =
		find_declarative_region<semantic_entities::open_declarative_region_shared_ptr_variant>
		(
			has_leading_double_colon,
			opt_nested_name_specifier_node,
			current_declarative_region
		)
	;

	//find entities in the last declarative region
	if(apply_using_directives_for_unqualified_id_part)
	{
		if(std::shared_ptr<semantic_entities::namespace_>* opt_namespace_ptr = utility::get<semantic_entities::namespace_>(&last_declarative_region))
		{
			return
				find_in_namespace
				<
					IdentifierGettingPolicy,
					Optional,
					Multiple,
					EntitiesT...
				>(identifier, *opt_namespace_ptr)
			;
		}
	}
	return
		find_local_entities
		<
			IdentifierGettingPolicy,
			semantic_entities::open_declarative_region_shared_ptr_variant,
			Optional,
			Multiple,
			EntitiesT...
		>(identifier, last_declarative_region)
	;
}



namespace detail
{

template<class DeclarativeRegionT>
typename return_type<false, false, DeclarativeRegionT>::type
find_declarative_region
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	if(has_leading_double_colon)
	{
		//the first declarative region is in the global namespace
		std::shared_ptr<semantic_entities::namespace_> global_namespace =
			semantic_entity_analysis::get_global_namespace(current_declarative_region)
		;

		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;

			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);
			std::string first_declarative_region_name;
			if(boost::optional<const syntax_nodes::identifier&> opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id_node))
				first_declarative_region_name = opt_identifier_node->value();
			else
				assert(false);

			//find the first declarative region
			typename return_type<false, false, DeclarativeRegionT>::type first_declarative_region =
				find_local_entities
				<
					semantic_entity_analysis::identifier_getting_policies::get_name,
					std::shared_ptr<semantic_entities::namespace_>,
					false,
					false,
					DeclarativeRegionT
				>(first_declarative_region_name, global_namespace)
			;

			//find the last declarative region
			return find_declarative_region<DeclarativeRegionT>(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			//both the first and last declarative regions ARE the global namespace
			return global_namespace;
		}
	}
	else
	{
		if(opt_nested_name_specifier_node)
		{
			auto nested_name_specifier_node = *opt_nested_name_specifier_node;
			auto identifier_or_template_id_node = get_identifier_or_template_id(nested_name_specifier_node);

			std::string first_declarative_region_name;
			if(boost::optional<const syntax_nodes::identifier&> opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id_node))
				first_declarative_region_name = opt_identifier_node->value();
			else
				assert(false);

			//find the first declarative region
			typename return_type<false, false, DeclarativeRegionT>::type first_declarative_region =
				find
				<
					semantic_entity_analysis::identifier_getting_policies::get_name,
					false,
					false,
					DeclarativeRegionT
				>(first_declarative_region_name, current_declarative_region)
			;

			//find the last declarative region
			return find_declarative_region<DeclarativeRegionT>(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			assert(false); //case already handled
		}
	}
}

template<class DeclarativeRegionT>
typename return_type<false, false, DeclarativeRegionT>::type
find_declarative_region
(
	const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
	const typename return_type<false, false, DeclarativeRegionT>::type& current_declarative_region
)
{
	if(auto opt_last_part_seq_node = get_last_part_seq(nested_name_specifier_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;

		typename return_type<false, false, DeclarativeRegionT>::type found_declarative_region = current_declarative_region;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			const syntax_nodes::nested_name_specifier_last_part& last_part_node = i->main_node();
			if(has_template_keyword(last_part_node))
			{
				assert(false); //not implemented yet (template)
			}
			else
			{
				const syntax_nodes::identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(last_part_node);
				if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id_node))
				{
					auto identifier_node = *opt_identifier_node;
					found_declarative_region =
						find_local_entities
						<
							semantic_entity_analysis::identifier_getting_policies::get_name,
							typename return_type<false, false, DeclarativeRegionT>::type,
							false,
							false,
							DeclarativeRegionT
						>
						(
							identifier_node.value(),
							found_declarative_region
						)
					;
				}
				else
				{
					assert(false); //not implemented yet (template)
				}
			}
		}

		return found_declarative_region;
	}
	else
	{
		return current_declarative_region;
	}
}

template<class IdentifierGettingPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find_in_namespace
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
)
{
	std::vector<std::shared_ptr<semantic_entities::namespace_>> already_searched_namespaces;
	return
		find_in_namespace
		<
			IdentifierGettingPolicy,
			Optional,
			Multiple,
			EntitiesT...
		>
		(
			identifier,
			current_namespace,
			already_searched_namespaces
		)
	;
}

template<class IdentifierGettingPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find_in_namespace
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	std::shared_ptr<semantic_entities::namespace_> current_namespace,
	std::vector<std::shared_ptr<semantic_entities::namespace_>>& already_searched_namespaces
)
{
	//search in the current namespace
	{
		already_searched_namespaces.push_back(current_namespace);

		typename return_type<true, Multiple, EntitiesT...>::type found_entities =
			find_local_entities
			<
				IdentifierGettingPolicy,
				std::shared_ptr<semantic_entities::namespace_>,
				true,
				Multiple,
				EntitiesT...
			>(identifier, current_namespace)
		;

		//if entities have been found, return them
		if(!utility::is_empty(found_entities))
			return std::move(return_result<Optional, Multiple, EntitiesT...>::result(found_entities));
	}

	//if no entity is found, search in using directive's namespaces
	typename return_type<true, true, EntitiesT...>::type found_entities;
	for
	(
		auto i = current_namespace->using_directive_namespaces().begin();
		i != current_namespace->using_directive_namespaces().end();
		++i
	)
	{
		std::shared_ptr<semantic_entities::namespace_> using_directive_namespace(*i);

		//make sure the namespace has not been already searched
		if
		(
			std::find
			(
				already_searched_namespaces.begin(),
				already_searched_namespaces.end(),
				using_directive_namespace
			) == already_searched_namespaces.end()
		)
		{
			add_to_result
			(
				found_entities,
				find_in_namespace<IdentifierGettingPolicy, true, Multiple, EntitiesT...>
				(
					identifier,
					using_directive_namespace,
					already_searched_namespaces
				)
			);
		}
	}

	return std::move(return_result<Optional, Multiple, EntitiesT...>::result(found_entities));
}



template<class IdentifierGettingPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT, class EntityT2, class... EntitiesT>
typename return_type<Optional, Multiple, EntityT, EntityT2, EntitiesT...>::type
find_local_entities
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	const DeclarativeRegionT& current_declarative_region
)
{
	typename return_type<true, Multiple, EntityT, EntityT2, EntitiesT...>::type found_entities;

	find_variadic_local_entities
	<
		IdentifierGettingPolicy,
		DeclarativeRegionT,
		Optional,
		Multiple,
		typename return_type<true, Multiple, EntityT, EntityT2, EntitiesT...>::type,
		EntityT,
		EntityT2,
		EntitiesT...
	>::find(identifier, current_declarative_region, found_entities);

	return return_result<Optional, Multiple, EntityT, EntityT2, EntitiesT...>::result(found_entities);
}

template<class IdentifierGettingPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT>
void
find_variadic_local_entities<IdentifierGettingPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT>::find
(
	const typename IdentifierGettingPolicy::identifier_t&,
	const DeclarativeRegionT&,
	ReturnT&
)
{
	//does nothing
}

template<class IdentifierGettingPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class ReturnT, class EntityT, class... EntitiesT>
void
find_variadic_local_entities<IdentifierGettingPolicy, DeclarativeRegionT, Optional, Multiple, ReturnT, EntityT, EntitiesT...>::find
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	const DeclarativeRegionT& current_declarative_region,
	ReturnT& found_entities
)
{
	//find entities of type EntityT in the current declarative region
	typename return_type<Optional, Multiple, EntityT>::type entities =
		find_local_entities
		<
			IdentifierGettingPolicy,
			DeclarativeRegionT,
			true,
			Multiple,
			EntityT
		>(identifier, current_declarative_region)
	;

	//if entities have been found...
	if(!utility::is_empty(entities))
	{
		//... add them to the list...
		add_to_result(found_entities, entities);

		//and stop if we want a single entity
		if(!Multiple) return;
	}

	//recursive call for other types of EntitiesT
	find_variadic_local_entities
	<
		IdentifierGettingPolicy,
		DeclarativeRegionT,
		true,
		Multiple,
		ReturnT,
		EntitiesT...
	>::find(identifier, current_declarative_region, found_entities);
}

template<class IdentifierGettingPolicy, class DeclarativeRegionT, bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find_local_entities
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	const DeclarativeRegionT& current_declarative_region
)
{
	using namespace semantic_entity_analysis;

	typename return_type<true, Multiple, EntityT>::type found_entities;

	typename get_members_type_traits<EntityT>::return_type members = get_members<EntityT>(current_declarative_region);
	for(auto i = members.begin(); i != members.end(); ++i)
	{
		auto current_entity = *i;
		if(IdentifierGettingPolicy::are_identifiers_equal(current_entity, identifier))
		{
			add_to_result(found_entities, current_entity);
			if(!Multiple) break;
		}
	}

	return std::move(return_result<Optional, Multiple, EntityT>::result(found_entities));
}

template<class IdentifierGettingPolicy, bool Optional, bool Multiple, class... EntitiesT>
typename return_type<Optional, Multiple, EntitiesT...>::type
find_entities_in_base_classes
(
	const typename IdentifierGettingPolicy::identifier_t& identifier,
	utility::shared_ptr_vector<semantic_entities::class_>::range base_classes
)
{
	using namespace semantic_entity_analysis;

	typename return_type<Optional, true, EntitiesT...>::type found_entities;

	for(auto i = base_classes.begin(); i != base_classes.end(); ++i)
	{
		std::shared_ptr<semantic_entities::class_> current_class = *i;

		//find entities in the current declarative region (i.e. current class)
		typename return_type<Optional, Multiple, EntitiesT...>::type current_class_found_entities =
			find_local_entities
			<
				IdentifierGettingPolicy,
				std::shared_ptr<semantic_entities::class_>,
				Optional,
				Multiple,
				EntitiesT...
			>(identifier, current_class)
		;

		//entities found?
		if(!utility::is_empty(current_class_found_entities))
		{
			//add them to the list
			add_to_result(found_entities, current_class_found_entities);
		}
		else
		{
			//find entities in the current declarative region's base classes
			typename return_type<Optional, Multiple, EntitiesT...>::type current_class_base_classes_found_entities =
				find_entities_in_base_classes
				<
					IdentifierGettingPolicy,
					Optional,
					Multiple,
					EntitiesT...
				>(identifier, current_class->base_classes())
			;

			//add them to the list
			add_to_result(found_entities, current_class_base_classes_found_entities);
		}
	}

	//If Multiple, return the full list.
	//If not Multiple, return the only one element of the list.
	return std::move(return_result<Optional, Multiple, EntitiesT...>::result(found_entities));
}



template<class T, class U>
void
add_to_result(T& result, const U& entity)
{
	result = entity;
}

template<class T, class U>
void
add_to_result(std::set<T>& result, const U& entity)
{
	if(!utility::is_empty(entity)) result.insert(entity);
}

template<class T, class U>
void
add_to_result(std::set<T>& result, const boost::optional<U>& entity)
{
	if(!utility::is_empty(entity)) result.insert(*entity);
}

template<class T, class U>
void
add_to_result(std::set<T>& result, const std::set<U>& entities)
{
	std::copy
	(
		entities.begin(),
		entities.end(),
		std::insert_iterator<std::set<T>>(result, result.end())
	);
}



template<class... EntitiesT>
typename return_type<true, false, EntitiesT...>::type
return_result<true, false, EntitiesT...>::result(typename return_type<true, true, EntitiesT...>::type& result)
{
	if(result.empty())
	{
		return typename return_type<true, false, EntitiesT...>::type(); //empty result
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... EntitiesT>
typename return_type<true, false, EntitiesT...>::type
return_result<true, false, EntitiesT...>::result(typename return_type<true, false, EntitiesT...>::type& result)
{
	return result;
}

template<class... EntitiesT>
typename return_type<false, false, EntitiesT...>::type
return_result<false, false, EntitiesT...>::result(typename return_type<false, true, EntitiesT...>::type& result)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... EntitiesT>
typename return_type<false, false, EntitiesT...>::type
return_result<false, false, EntitiesT...>::result(typename return_type<true, false, EntitiesT...>::type& result)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return result;
}

template<class... EntitiesT>
typename return_type<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type
return_result<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::result
(
	typename return_type<false, true, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type& result
)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class... EntitiesT>
typename return_type<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type
return_result<false, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::result
(
	typename return_type<true, false, utility::basic_variant<utility::add_shared_ptr, EntitiesT...>>::type& result
)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return *result;
}

template<class EntityT, class EntityT2, class... EntitiesT>
typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
return_result<false, false, EntityT, EntityT2, EntitiesT...>::result
(
	typename return_type<false, true, EntityT, EntityT2, EntitiesT...>::type& result
)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return *result.begin();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class EntityT, class EntityT2, class... EntitiesT>
typename return_type<false, false, EntityT, EntityT2, EntitiesT...>::type
return_result<false, false, EntityT, EntityT2, EntitiesT...>::result
(
	typename return_type<true, false, EntityT, EntityT2, EntitiesT...>::type& result
)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return *result;
}

template<class... EntitiesT>
typename return_type<true, true, EntitiesT...>::type&
return_result<true, true, EntitiesT...>::result(typename return_type<true, true, EntitiesT...>::type& result)
{
	return result;
}

template<class... EntitiesT>
typename return_type<false, true, EntitiesT...>::type&
return_result<false, true, EntitiesT...>::result(typename return_type<true, true, EntitiesT...>::type& result)
{
	if(result.empty())
		throw std::runtime_error("no entity found");
	return result;
}

} //namespace detail

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup

#endif

