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

#include "name_lookup2.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

utility::shared_ptr_vector<semantic_entities::named_entity>
name_lookup2::find_entities
(
	utility::shared_ptr_vector<semantic_entities::scope>::range scope_path,
	const std::string& name
)
{
	//find entities from current to outermost scopes (until global namespace)
	std::reverse(scope_path.begin(), scope_path.end()); //TODO it would be faster if scope_path could provide a bidirectional iterator
	for(auto i = scope_path.begin(); i != scope_path.end(); ++i)
	{
		std::shared_ptr<semantic_entities::scope> current_scope = *i;

		//find entities in current scope
		utility::shared_ptr_vector<semantic_entities::named_entity> found_entities = find_entities(current_scope, name);
		if(!found_entities.empty()) return found_entities;
	}

	throw std::runtime_error("No entity found");
}

utility::shared_ptr_vector<semantic_entities::named_entity>
name_lookup2::find_entities
(
	std::shared_ptr<semantic_entities::scope> current_scope,
	const std::string& name
)
{
	utility::shared_ptr_vector<semantic_entities::named_entity> found_entities;

	for(auto i = current_scope->named_entities().begin(); i != current_scope->named_entities().end(); ++i)
	{
		std::shared_ptr<semantic_entities::named_entity> current_entity = *i;
		if(current_entity->name() == name)
		{
			found_entities.push_back(current_entity);
		}
	}

	return found_entities;
}

std::shared_ptr<semantic_entities::named_scope>
name_lookup2::find_scope
(
	utility::shared_ptr_vector<semantic_entities::scope>::range scope_path,
	const std::string& name
)
{
	std::reverse(scope_path.begin(), scope_path.end()); //TODO it would be faster if scope_path could provide a bidirectional iterator
	for(auto i = scope_path.begin(); i != scope_path.end(); ++i) //from current to outermost scopes (until global namespace)
	{
		std::shared_ptr<semantic_entities::scope> current_scope = *i;

		//find scope in current scope
		std::shared_ptr<semantic_entities::named_scope> found_scope = find_scope(current_scope, name);
		if(found_scope) return found_scope;
	}

	throw std::runtime_error("No scope found");
}

std::shared_ptr<semantic_entities::named_scope>
name_lookup2::find_scope
(
	std::shared_ptr<semantic_entities::scope> current_scope,
	const std::string& name
)
{
	std::shared_ptr<semantic_entities::named_scope> found_scope;

	auto scopes = current_scope->named_scopes();
	auto scope_it = std::find_if
	(
		scopes.begin(),
		scopes.end(),
		std::bind
		(
			std::equal_to<std::string>(),
			std::cref(name),
			std::bind
			(
				&semantic_entities::named_scope::name,
				std::placeholders::_1
			)
		)
	);

	if(scope_it != scopes.end()) //if a name has been found
	{
		found_scope = *scope_it;
	}

	return found_scope;
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

