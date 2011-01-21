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
#include <scalpel/utility/shared_ptr_variant.hpp>
#include <boost/test/unit_test.hpp>

namespace name_lookup
{

BOOST_AUTO_TEST_CASE(test_case_12)
{
	using namespace scalpel::cpp::syntax_nodes;
	using namespace scalpel::cpp::semantic_entities;
	using namespace scalpel::cpp::semantic_analysis::detail::name_lookup;
	using namespace scalpel::cpp::semantic_analysis::detail::semantic_entity_analysis;

	//
	//construction of the semantic graph of the following source code:
	/*
		class c
		{
		};

		namespace n
		{
			class c
			{
			};
		}
	*/

	//namespaces
	auto semantic_graph = scalpel::cpp::semantic_graph::make_shared();
	auto namespace_n = scalpel::cpp::semantic_graph::make_shared("n");

	//classes
	auto class_c = class_::make_shared("c");
	auto class_n_c = class_::make_shared("c");

	//assembling
	semantic_graph->add_member(class_c);
	semantic_graph->add_member(namespace_n);
	namespace_n->add_member(class_n_c);



	//
	//name lookup test
	//

	//look up c from namespace n, must find n::c
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, class_>
			(
				"c",
				namespace_n.get()
			)
		;

		BOOST_CHECK_EQUAL(found_entity, class_n_c);
	}

	//look up ::c from namespace n, must find c
	{
		auto found_entity =
			find<identification_policies::by_name, false, false, class_>
			(
				true,
				optional_node<nested_name_specifier>(),
				"c",
				namespace_n.get()
			)
		;

		BOOST_CHECK_EQUAL(found_entity, class_c);
	}
}

} //namespace name_lookup

