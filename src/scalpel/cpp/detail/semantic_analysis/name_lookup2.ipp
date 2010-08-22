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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_IPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_IPP

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis { namespace name_lookup2
{

template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find_entities
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	//Check whether the given qualified name is really qualified.
	//If not, perform a simple unqualified name lookup.
	if
	(
		!has_leading_double_colon(nested_identifier_or_template_id_node) &&
		!get_nested_name_specifier(nested_identifier_or_template_id_node)
	)
	{
		auto identifier_or_template_id_node = syntax_nodes::get_identifier_or_template_id(nested_identifier_or_template_id_node);
		return find_entities<Optional, Multiple, EntityT>(identifier_or_template_id_node, current_declarative_region);
	}

	//Get the last declarative region of the nested name specifier
	//(i.e. Z in "[::]X::Y::Z::").
	semantic_entities::declarative_region_shared_ptr_variant last_declarative_region =
		impl::find_declarative_region(nested_identifier_or_template_id_node, current_declarative_region)
	;

	//find entities in the last declarative region
	auto identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);
	return impl::find_entities_in_declarative_region<Optional, Multiple, EntityT>(identifier_or_template_id_node, last_declarative_region);
}

template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
find_entities
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	const semantic_entities::declarative_region_shared_ptr_variant& current_declarative_region
)
{
	if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id))
	{
		auto identifier_node = *opt_identifier_node;
		return impl::find_entities_from_identifier<Optional, Multiple, EntityT>(identifier_node.value(), current_declarative_region);
	}
	else
	{
		throw std::runtime_error("Not implemented yet");
	}
}



template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
impl::find_entities_from_identifier
(
	const std::string& name,
	semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	typename return_type<true, Multiple, EntityT>::type found_entities;

	//find entities from current to outermost declarative regions
	//(until global namespace)
	while(true)
	{
		//find entities in this declarative region
		found_entities =
			find_entities_from_identifier_in_declarative_region<true, Multiple, EntityT>(name, current_declarative_region)
		;
		if(!utility::is_empty(found_entities)) break;

		//only for classes...
		if(auto opt_class_ptr = utility::get<std::shared_ptr<semantic_entities::class_>>(&current_declarative_region))
		{
			std::shared_ptr<semantic_entities::class_> class_ptr = *opt_class_ptr;

			//find entities in the base classes of that class
			found_entities =
				find_entities_in_base_classes<true, Multiple, EntityT>(name, class_ptr->base_classes())
			;
			if(!utility::is_empty(found_entities)) break;
		}

		if(!has_declarative_region(current_declarative_region)) break;
		current_declarative_region = get_declarative_region(current_declarative_region);
	}

	return std::move(return_result<Optional, Multiple, EntityT>::result(found_entities));
}

template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
typename return_type<Optional, Multiple, EntityT>::type
impl::find_entities_in_declarative_region
(
	const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
	DeclarativeRegionT& current_declarative_region
)
{
	if(auto opt_identifier_node = syntax_nodes::get<syntax_nodes::identifier>(&identifier_or_template_id))
	{
		auto identifier_node = *opt_identifier_node;
		return find_entities_from_identifier_in_declarative_region<Optional, Multiple, EntityT>(identifier_node.value(), current_declarative_region);
	}
	else
	{
		throw std::runtime_error("Not implemented yet");
	}
}

template<bool Optional, bool Multiple, class EntityT, class DeclarativeRegionT>
typename return_type<Optional, Multiple, EntityT>::type
impl::find_entities_from_identifier_in_declarative_region
(
	const std::string& name,
	DeclarativeRegionT& current_declarative_region
)
{
	typename return_type<true, Multiple, EntityT>::type found_entities;

	typename get_members_type_traits<EntityT>::return_type members = get_members<EntityT>(current_declarative_region);
	for(auto i = members.begin(); i != members.end(); ++i)
	{
		auto current_entity = *i;
		if(get_name(current_entity) == name)
		{
			add_to_result(found_entities, current_entity);
			if(!Multiple) break;
		}
	}

	return std::move(return_result<Optional, Multiple, EntityT>::result(found_entities));
}

template<bool Optional, bool Multiple, class EntityT>
typename return_type<Optional, Multiple, EntityT>::type
impl::find_entities_in_base_classes
(
	const std::string& name,
	utility::vector<std::shared_ptr<semantic_entities::class_>>::range base_classes
)
{
	typename return_type<Optional, true, EntityT>::type found_entities;

	for(auto i = base_classes.begin(); i != base_classes.end(); ++i)
	{
		std::shared_ptr<semantic_entities::class_> current_class = *i;

		//find entities in the current declarative region (i.e. current class)
		typename return_type<Optional, Multiple, EntityT>::type current_class_found_entities =
			find_entities_from_identifier_in_declarative_region<Optional, Multiple, EntityT>(name, current_class)
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
			typename return_type<Optional, Multiple, EntityT>::type current_class_base_classes_found_entities =
				find_entities_in_base_classes<Optional, Multiple, EntityT>(name, current_class->base_classes())
			;

			//add them to the list
			add_to_result(found_entities, current_class_base_classes_found_entities);
		}
	}

	//If Multiple, return the full list.
	//If not Multiple, return the only one element of the list.
	return std::move(return_result<Optional, Multiple, EntityT>::result(found_entities));
}



template<class T, class T2>
void
impl::add_to_result(T& result, T2& entity)
{
	result = entity;
}

template<class T, class T2>
void
impl::add_to_result(utility::vector<T>& result, T2& entity)
{
	if(!utility::is_empty(entity)) result.push_back(entity);
}

template<class T, class T2>
void
impl::add_to_result(utility::vector<T>& result, boost::optional<T2>& entity)
{
	if(!utility::is_empty(entity)) result.push_back(*entity);
}

template<class T, class T2>
void
impl::add_to_result(utility::vector<T>& result, utility::vector<T2>& entities)
{
	std::copy
	(
		entities.begin(),
		entities.end(),
		std::back_insert_iterator<utility::vector<T>>(result)
	);
}



template<class EntityT>
typename return_type<true, false, EntityT>::type
impl::return_result<true, false, EntityT>::result(typename return_type<true, true, EntityT>::type& result)
{
	if(result.empty())
	{
		return typename return_type<true, false, EntityT>::type(); //empty result
	}
	else if(result.size() == 1)
	{
		return result.front();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class EntityT>
typename return_type<true, false, EntityT>::type
impl::return_result<true, false, EntityT>::result(typename return_type<true, false, EntityT>::type& result)
{
	return result;
}

template<class EntityT>
typename return_type<false, false, EntityT>::type
impl::return_result<false, false, EntityT>::result(typename return_type<false, true, EntityT>::type& result)
{
	if(result.empty())
	{
		throw std::runtime_error("no entity found");
	}
	else if(result.size() == 1)
	{
		return result.front();
	}
	else
	{
		throw std::runtime_error("more than one entities found");
	}
}

template<class EntityT>
typename return_type<false, false, EntityT>::type
impl::return_result<false, false, EntityT>::result(typename return_type<true, false, EntityT>::type& result)
{
	if(!result)
		throw std::runtime_error("no entity found");
	return *result;
}

template<class EntityT>
utility::vector<std::shared_ptr<EntityT>>&
impl::return_result<true, true, EntityT>::result(utility::vector<std::shared_ptr<EntityT>>& result)
{
	return result;
}

template<class EntityT>
utility::vector<std::shared_ptr<EntityT>>&
impl::return_result<false, true, EntityT>::result(utility::vector<std::shared_ptr<EntityT>>& result)
{
	if(result.empty())
		throw std::runtime_error("no entity found");
	return result;
}

}}}}} //namespace scalpel::cpp::detail::semantic_analysis::name_lookup2

#endif

