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

#include "analyzer.hpp"
#include <boost/test/unit_test.hpp>

namespace semantic_analysis
{

BOOST_AUTO_TEST_CASE(simple_free_function)
{
	using namespace scalpel::cpp::semantic_entities;

	std::shared_ptr<scalpel::cpp::semantic_graph> semantic_graph = analyze
	(
		"int "
		"main() "
		"{ "
		"} "
	);

	auto expected_semantic_graph = namespace_::make_shared();
	auto function_main = std::make_shared<simple_function>("main", fundamental_type_shared_ptrs::int_);

	expected_semantic_graph->add_member(function_main);
	function_main->body(std::make_shared<statement_block>());

	BOOST_CHECK(*semantic_graph == *expected_semantic_graph);
}

} //namespace semantic_analysis

