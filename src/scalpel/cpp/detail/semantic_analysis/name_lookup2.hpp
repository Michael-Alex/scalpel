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

#ifndef SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_HPP
#define SCALPEL_CPP_DETAIL_SEMANTIC_ANALYSIS_NAME_LOOKUP2_HPP

#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <scalpel/utility/shared_ptr_vector.hpp>
#include <memory>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

class name_lookup2
{
	public:
		/**
		Find entities corresponding to the given nested identifier
		(or nested template-id),
		from the given declarative region path (qualified name lookup)
		*/
		template<class EntityT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities
		(
			const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

	private:
		/**
		Find the declarative region corresponding to the given syntax node
		(i.e. Z in the expression "X::Y::Z::"),
		from the given declarative region
		*/
		template<class DeclarativeRegionT, class CurrentDeclarativeRegionT>
		static
		std::shared_ptr<DeclarativeRegionT>
		find_declarative_region
		(
			const syntax_nodes::nested_name_specifier_last_part_seq& nested_name_specifier_last_part_seq_node,
			std::shared_ptr<CurrentDeclarativeRegionT> current_declarative_region
		);

	public:
		/**
		Find entities corresponding to the given identifier_or_template_id node,
		from the given declarative region path (unqualified name lookup)
		*/
		template<class EntityT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities
		(
			const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

	private:
		/**
		Find entities corresponding to the given name,
		from the given declarative region path (unqualified name lookup)
		*/
		template<class EntityT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities_from_identifier
		(
			const std::string& name,
			std::vector<semantic_entities::declarative_region_variant>& declarative_region_path
		);

		/**
		Find entities corresponding to the given identifier_or_template_id node,
		in the given declarative region only
		*/
		template<class EntityT, class DeclarativeRegionT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities_in_declarative_region
		(
			const syntax_nodes::identifier_or_template_id& identifier_or_template_id,
			std::shared_ptr<DeclarativeRegionT> current_declarative_region
		);

		/**
		Find entities of the given name, in the given declarative region only
		*/
		template<class EntityT, class DeclarativeRegionT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities_from_identifier_in_declarative_region
		(
			const std::string& name,
			std::shared_ptr<DeclarativeRegionT> current_declarative_region
		);

		/**
		Find entities of the given name, in the given base classes
		*/
		template<class EntityT>
		static
		utility::shared_ptr_vector<EntityT>
		find_entities_in_base_classes
		(
			const std::string& name,
			utility::shared_ptr_vector<semantic_entities::class_>::range base_classes
		);

	private:
		template<class MemberT, class ParentT>
		static
		typename utility::shared_ptr_vector<MemberT>::range
		get_members(std::shared_ptr<ParentT> parent);
};

}}}} //namespace scalpel::cpp::detail::semantic_analysis

#include "name_lookup2.ipp"

#endif

