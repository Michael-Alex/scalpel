/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#include <scalpel/cpp/semantic_analysis/detail/name_lookup.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/cpp/syntax_tree.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(test_case_8)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
	namespace b
	{
		int i;
	}

	namespace a
	{
		using namespace b;
		int j;
	}

	namespace b
	{
		using namespace a;
	}

	void test()
	{
	}
	*/

	//namespaces
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");
	auto namespace_b = new namespace_("b");

	//functions
	auto function_test = new simple_function
	(
		"test",
		fundamental_type::VOID
	);

	//variables
	auto variable_b_i = new variable
	(
		"i",
		fundamental_type::INT
	);
	auto variable_a_j = new variable
	(
		"j",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	//namespace_a->add_using_directive_namespace(*namespace_b);
	namespace_a->add_member(std::unique_ptr<variable>(variable_a_j));
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_b));
	//namespace_b->add_using_directive_namespace(*namespace_a);
	namespace_b->add_member(std::unique_ptr<variable>(variable_b_i));
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_test));



	//
	//name lookup test
	//

	//look up a::j from function test, must find a::j
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("a"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"j",
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_j);
	}

	//look up b::j from function test, must find a::j
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("b"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"j",
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_j);
	}

	//look up a::i from function test, must find b::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("a"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up b::i from function test, must find b::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("b"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				function_test
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up b::k from function test, must find nothing
	{
		auto found_entity =
			find<identification_policies::by_name, true, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("b"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"k",
				function_test
			)
		;
		BOOST_CHECK(!found_entity);
	}
}

} //namespace name_lookup

