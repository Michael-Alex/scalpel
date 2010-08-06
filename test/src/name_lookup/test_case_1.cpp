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

#include "test_case_1.hpp"
#include <scalpel/cpp/detail/semantic_analysis/name_lookup2.hpp>
#include <scalpel/cpp/semantic_graph.hpp>
#include <scalpel/utility/null_deleter.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

void
test_case_1()
{
	//
	//construction of the semantic graph of the following source code:
	/*
	namespace A
	{
		int i;

		namespace B
		{
			void f();
		}

		namespace C
		{
		}
	}

	int i, j;

	void A::B::f()
	{
		//look from here
	}
	*/
	auto semantic_graph = std::make_shared<scalpel::cpp::semantic_graph>();
	auto variable_a_i = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"i",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto namespace_a = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("A");
	auto variable_i = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"i",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto variable_j = std::make_shared<scalpel::cpp::semantic_entities::variable>
	(
		"j",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::int_
	);
	auto namespace_b = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("B");
	auto function_f = std::make_shared<scalpel::cpp::semantic_entities::simple_function>
	(
		"f",
		scalpel::cpp::semantic_entities::built_in_type_shared_ptrs::void_
	);
	auto namespace_c = std::make_shared<scalpel::cpp::semantic_entities::namespace_>("C");

	semantic_graph->add(namespace_a);
	namespace_a->add(variable_a_i);
	namespace_a->add(namespace_b);
	namespace_b->add(function_f);
	namespace_a->add(namespace_c);
	semantic_graph->add(variable_i);
	semantic_graph->add(variable_j);



	//
	//scope path construction
	//
	scalpel::utility::shared_ptr_vector<scalpel::cpp::semantic_entities::scope> scope_path;
	scope_path.push_back(semantic_graph);
	scope_path.push_back(namespace_a);
	scope_path.push_back(namespace_b);
	scope_path.push_back(function_f);



	//
	//name lookup test
	//
	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(scope_path, "i");
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		BOOST_CHECK_EQUAL(found_entities.front(), variable_a_i);
	}

	{
		auto found_entities = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_entities(scope_path, "j");
		BOOST_CHECK_EQUAL(found_entities.size(), 1);
		BOOST_CHECK_EQUAL(found_entities.front(), variable_j);
	}

	{
		auto found_scope = scalpel::cpp::detail::semantic_analysis::name_lookup2::find_scope(scope_path, "C");
		BOOST_CHECK_EQUAL(found_scope, namespace_c);
	}
}

} //namespace name_lookup

