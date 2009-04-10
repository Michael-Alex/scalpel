/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_TREE_ASSIGNMENT_EXPRESSION_HPP

#include "composite_node.hpp"
#include "assignment_operator.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class assignment_expression: public composite_node
{
    public:
        assignment_expression
        (
            assignment_operator&& an_assignment_operator
        );

		assignment_expression(const assignment_expression& o);

		assignment_expression(assignment_expression&& o);

		const assignment_expression&
		operator=(const assignment_expression& o);

        inline
        const assignment_operator&
        get_assignment_operator() const;

    private:
		void
		update_node_list();

        //logical_or_expression logical_or_expression_;
        assignment_operator assignment_operator_;
        //std::shared_ptr<> ;
};

inline
const assignment_operator&
assignment_expression::get_assignment_operator() const
{
    return assignment_operator_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
