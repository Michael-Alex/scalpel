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

#include "test_case_10.hpp"
#include <scalpel/cpp/detail/semantic_analysis/semantic_graph_analysis/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_10()
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::detail::semantic_analysis::semantic_graph_analysis::name_lookup;

	//
	//construction of the semantic graph of the following source code:
	/*
	namespace a
	{
		int i;
	}

	namespace as = a;

	void
	test()
	{
		namespace as2 = a;
		as::i = 0;
		as2::i = 0;
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("a");

	//namespace aliases
	auto namespace_alias_as = std::make_shared<namespace_alias>("as", namespace_a);
	auto namespace_alias_as2 = std::make_shared<namespace_alias>("as2", namespace_a);

	//functions
	auto function_test = simple_function::make_shared
	(
		"test",
		fundamental_type_shared_ptrs::void_
	);

	//variables
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type_shared_ptrs::int_
	);

	//assembling
	semantic_graph->add_member(namespace_a);
	namespace_a->add_member(variable_a_i);
	semantic_graph->add_member(namespace_alias_as);
	semantic_graph->add_member(function_test);
	function_test->body(std::make_shared<statement_block>());
	function_test->body()->add_member(namespace_alias_as2);



	//
	//name lookup test
	//

	//look up as::i from function test, must find a::i
	{
		nested_identifier_or_template_id as_i_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("as"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("i")
		);
		auto found_entity = find<variable>(as_i_syntax_node, function_test->body());
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//look up as2::i from function test, must find a::i
	{
		nested_identifier_or_template_id as2_i_syntax_node
		(
			optional_node<predefined_text_node<str::double_colon>>(),
			space(""),
			nested_name_specifier
			(
				identifier("as2"),
				space(""),
				predefined_text_node<str::double_colon>(),
				space(""),
				optional_node<nested_name_specifier_last_part_seq>()
			),
			space(""),
			identifier("i")
		);
		auto found_entity = find<variable>(as2_i_syntax_node, function_test->body());
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}
}

} //namespace name_lookup

