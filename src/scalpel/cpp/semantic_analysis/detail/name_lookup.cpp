/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "name_lookup.hpp"
#include <stdexcept>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail { namespace name_lookup
{

using namespace semantic_entities;

semantic_entities::open_declarative_region_t
find_declarative_region
(
	const bool has_leading_double_colon,
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node,
	const semantic_entities::declarative_region_t& current_declarative_region
)
{
	if(has_leading_double_colon)
	{
		//the first declarative region is the global namespace
		semantic_entities::namespace_& global_namespace =
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

			//find the second declarative region
			open_declarative_region_t first_declarative_region =
				detail::find_local_entities
				<
					semantic_entity_analysis::identification_policies::by_name,
					semantic_entities::namespace_,
					false,
					false,
					open_declarative_region_t
				>(first_declarative_region_name, global_namespace)
			;

			//find the last declarative region
			return detail::find_declarative_region(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			//both the first and last declarative regions ARE the global namespace
			return &global_namespace;
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
			open_declarative_region_t first_declarative_region =
				find
				<
					semantic_entity_analysis::identification_policies::by_name,
					false,
					false,
					open_declarative_region_t
				>(first_declarative_region_name, current_declarative_region)
			;

			//find the last declarative region
			return detail::find_declarative_region(nested_name_specifier_node, first_declarative_region);
		}
		else
		{
			//error
			assert(false);

			//we could simply return current_declarative_region here,
			//but the cast to open_declarative_region_t
			//could raise an exception
		}
	}
}

namespace detail
{

semantic_entities::open_declarative_region_t
find_declarative_region
(
	const syntax_nodes::nested_name_specifier& nested_name_specifier_node,
	const semantic_entities::open_declarative_region_t& current_declarative_region
)
{
	if(auto opt_last_part_seq_node = get_last_part_seq(nested_name_specifier_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;

		open_declarative_region_t found_declarative_region = current_declarative_region;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			const syntax_nodes::nested_name_specifier_last_part& last_part_node = *i;
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
							semantic_entity_analysis::identification_policies::by_name,
							open_declarative_region_t,
							false,
							false,
							open_declarative_region_t
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

} //namespace detail

}}}}} //namespace scalpel::cpp::semantic_analysis::detail::name_lookup

