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

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

//symbols
const leaf_node ampersand("&");
const leaf_node arrow_and_asterisk("->*");
const leaf_node asterisk("*");
const leaf_node capital_l("L");
const leaf_node circumflex("^");
const leaf_node closing_brace("}");
const leaf_node closing_bracket(")");
const leaf_node colon(":");
const leaf_node comma(",");
const leaf_node dot_and_asterisk(".*");
const leaf_node double_ampersand("&&");
const leaf_node double_colon("::");
const leaf_node double_equal("==");
const leaf_node double_left_angle_bracket("<<");
const leaf_node double_pipe("||");
const leaf_node double_quote("\"");
const leaf_node double_right_angle_bracket(">>");
const leaf_node empty("");
const leaf_node inequal("!=");
const leaf_node left_angle_bracket("<");
const leaf_node left_angle_bracket_and_equal("<=");
const leaf_node minus("-");
const leaf_node opening_brace("{");
const leaf_node opening_bracket("(");
const leaf_node percent("%");
const leaf_node pipe("|");
const leaf_node plus("+");
const leaf_node right_angle_bracket(">");
const leaf_node right_angle_bracket_and_equal(">=");
const leaf_node semicolon(";");
const leaf_node single_quote("'");
const leaf_node slash("/");

//keywords
const leaf_node break_keyword("break");
const leaf_node continue_keyword("continue");
const leaf_node goto_keyword("goto");
const leaf_node return_keyword("return");

}}} //namespace socoa::cpp::syntax_tree

