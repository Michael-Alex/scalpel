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

BOOST_AUTO_TEST_CASE(test_case_5)
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

	namespace b
	{
		int i;
		int j;

		namespace c
		{
			namespace d
			{
				using namespace a;
				int j;
				int k;
			}
			using namespace d;
			int k = 89;
		}
	}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_a = namespace_::make_shared("a");
	auto namespace_b = namespace_::make_shared("b");
	auto namespace_c = namespace_::make_shared("c");
	auto namespace_d = namespace_::make_shared("d");

	//variables
	auto variable_a_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto variable_b_i = std::make_shared<variable>
	(
		"i",
		fundamental_type::INT
	);
	auto variable_b_j = std::make_shared<variable>
	(
		"j",
		fundamental_type::INT
	);
	auto variable_c_k = std::make_shared<variable>
	(
		"k",
		fundamental_type::INT
	);
	auto variable_d_j = std::make_shared<variable>
	(
		"j",
		fundamental_type::INT
	);
	auto variable_d_k = std::make_shared<variable>
	(
		"k",
		fundamental_type::INT
	);

	//assembling
	semantic_graph->add_member(namespace_a);
	namespace_a->add_member(variable_a_i);
	semantic_graph->add_member(namespace_b);
	namespace_b->add_member(variable_b_i);
	namespace_b->add_member(variable_b_j);
	namespace_b->add_member(namespace_c);
	namespace_c->add_member(namespace_d);
	namespace_d->add_using_directive_namespace(namespace_a);
	namespace_d->add_member(variable_d_j);
	namespace_d->add_member(variable_d_k);
	namespace_c->add_using_directive_namespace(namespace_d);
	namespace_c->add_member(variable_c_k);



	//
	//name lookup test
	//

	//look up i from namespace d, must find b::i
	{
		auto found_entity = find<identification_policies::by_name, false, false, variable>("i", namespace_d);
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up k from namespace c, must find c::k and d::k
	{
		auto found_entities = find<identification_policies::by_name, false, true, variable>("k", namespace_c);
		BOOST_CHECK_EQUAL(found_entities.size(), 2);
		if(found_entities.size() == 2)
		{
			BOOST_CHECK(found_entities.find(variable_c_k) != found_entities.end());
			BOOST_CHECK(found_entities.find(variable_d_k) != found_entities.end());
		}
	}

	//look up i from namespace c, must find b::i
	{
		auto found_entity = find<identification_policies::by_name, false, false, variable>("i", namespace_c);
		BOOST_CHECK_EQUAL(found_entity, variable_b_i);
	}

	//look up j from namespace c, must find d::j
	{
		auto found_entity = find<identification_policies::by_name, false, false, variable>("j", namespace_c);
		BOOST_CHECK_EQUAL(found_entity, variable_d_j);
	}
}

} //namespace name_lookup

