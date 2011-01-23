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

BOOST_AUTO_TEST_CASE(test_case_10)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

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
	scalpel::cpp::semantic_graph semantic_graph;
	auto namespace_a = new namespace_("a");

	//namespace aliases
	auto namespace_alias_as = new namespace_alias("as", *namespace_a);
	auto namespace_alias_as2 = new namespace_alias("as2", *namespace_a);

	//functions
	auto function_test = new simple_function
	(
		"test",
		fundamental_type::VOID
	);

	//variables
	auto variable_a_i = new variable
	(
		"i",
		fundamental_type::INT
	);

	//assembling
	semantic_graph.add_member(std::unique_ptr<namespace_>(namespace_a));
	namespace_a->add_member(std::unique_ptr<variable>(variable_a_i));
	semantic_graph.add_member(std::unique_ptr<namespace_alias>(namespace_alias_as));
	semantic_graph.add_member(std::unique_ptr<simple_function>(function_test));
	function_test->body(std::unique_ptr<statement_block>(new statement_block()));
	function_test->body().add_member(std::unique_ptr<namespace_alias>(namespace_alias_as2));



	//
	//name lookup test
	//

	//look up as::i from function test, must find a::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("as"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				&function_test->body()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//look up as2::i from function test, must find a::i
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, variable>
			(
				false,
				nested_name_specifier
				(
					identifier("as2"),
					space(""),
					predefined_text_node<str::double_colon>(),
					space(""),
					optional_node<nested_name_specifier_last_part_seq>()
				),
				"i",
				&function_test->body()
			)
		;
		BOOST_CHECK_EQUAL(found_entity, variable_a_i);
	}

	//look up a from as, must find a
	{
		scalpel::utility::ptr_variant<namespace_, namespace_alias>::type found_entity =
			find<identification_policies::by_name, false, false, namespace_, namespace_alias>("as", &function_test->body())
		;
		namespace_alias* found_namespace_alias = get<namespace_alias>(found_entity);
		BOOST_CHECK_EQUAL(found_namespace_alias, namespace_alias_as);
		BOOST_CHECK_EQUAL(&found_namespace_alias->referred_namespace(), namespace_a);
	}
}

} //namespace name_lookup

