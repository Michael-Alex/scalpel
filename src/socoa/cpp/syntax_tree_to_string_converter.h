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

#ifndef SOCOA_CPP_SYNTAX_TREE_TO_STRING_CONVERTER_H
#define SOCOA_CPP_SYNTAX_TREE_TO_STRING_CONVERTER_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include "syntax_tree.h"

#define CONVERT_DECLARATION(type)                       \
void                                                    \
convert(const syntax_tree::type& item);

namespace socoa { namespace cpp
{

class syntax_tree_to_string_converter
{
	private:
		class static_visitor: public boost::static_visitor<>
		{
			public:
				static_visitor(syntax_tree_to_string_converter& converter):
					converter_(converter)
				{
				}

				template<class T>
				void
				operator()(const T& item) const
				{
					return converter_.convert(item);
				}

			private:
				syntax_tree_to_string_converter& converter_;
		};

    public:
        syntax_tree_to_string_converter();

        std::string
        operator()(const syntax_tree_t& a_syntax_tree);

    private:
        CONVERT_DECLARATION(identifier)
        CONVERT_DECLARATION(qualified_nested_id)
        CONVERT_DECLARATION(qualified_operator_function_id)
        CONVERT_DECLARATION(qualified_template_id)
        CONVERT_DECLARATION(qualified_identifier)
        CONVERT_DECLARATION(nested_name_specifier)
        CONVERT_DECLARATION(nested_name_specifier_template_id_part)
        CONVERT_DECLARATION(simple_template_type_specifier)
        CONVERT_DECLARATION(namespace_definition)
        CONVERT_DECLARATION(using_declaration)
        CONVERT_DECLARATION(using_directive)
        CONVERT_DECLARATION(init_declarator)
        CONVERT_DECLARATION(declarator)
        CONVERT_DECLARATION(direct_declarator)
        CONVERT_DECLARATION(direct_declarator_function_part)
        CONVERT_DECLARATION(direct_declarator_array_part)
        CONVERT_DECLARATION(ptr_operator)
        CONVERT_DECLARATION(cv_qualifier)
        CONVERT_DECLARATION(parameter_declaration_clause)
        CONVERT_DECLARATION(parameter_declaration)
        CONVERT_DECLARATION(function_definition)
        CONVERT_DECLARATION(class_specifier)
        CONVERT_DECLARATION(class_head)
        CONVERT_DECLARATION(member_specification)
        CONVERT_DECLARATION(member_specification_access_specifier)
        CONVERT_DECLARATION(member_declaration_member_declarator_list)
        CONVERT_DECLARATION(member_declaration_unqualified_id)
        CONVERT_DECLARATION(member_declaration_function_definition)
        CONVERT_DECLARATION(member_declarator_declarator)
        CONVERT_DECLARATION(member_declarator_bit_field_member)
        CONVERT_DECLARATION(ctor_initializer)
        CONVERT_DECLARATION(mem_initializer)
        CONVERT_DECLARATION(template_declaration)
        CONVERT_DECLARATION(simple_declaration)
        CONVERT_DECLARATION(template_id)
        CONVERT_DECLARATION(nested_identifier_or_template_id)

		void
		convert(const syntax_tree::decl_specifier_seq& seq);

        template<class T, const std::string& Separator>
        void
        convert(const util::sequence<T, Separator>& seq);

        template<const std::vector<std::string>& StringList>
        void
        convert(const util::string_enumeration<StringList>& a_string_enumeration);

        template<class T>
        inline
        void
        safe_convert(T item);

        template<class T>
        void
        safe_convert(const boost::optional<T> item);

		template<class T, class U>
		void
		safe_convert(const boost::variant<T, U> item);

        void
        add_space();

        const std::string
        new_line();

        const std::string
        opening_brace();

        const std::string
        closing_brace();

        const std::string
        indentation();

		static_visitor static_visitor_;
        std::ostringstream result_;
        unsigned int indentation_level_;
};

template<class T, const std::string& Separator>
void
syntax_tree_to_string_converter::convert(const util::sequence<T, Separator>& seq)
{
    typedef typename util::sequence<T>::list_t item_list_t;

    for(typename item_list_t::const_iterator i = seq.get_items().begin(); i != seq.get_items().end(); ++i)
    {
        //add separator
        if(i != seq.get_items().begin()) //don't add a separator before the first item
            result_ << Separator << ' ';

        safe_convert(*i);
    }
}

template<const std::vector<std::string>& StringList>
void
syntax_tree_to_string_converter::convert(const util::string_enumeration<StringList>& a_string_enumeration)
{
    add_space();
    result_ << a_string_enumeration.get_value();
}

template<class T>
void
syntax_tree_to_string_converter::safe_convert(T item)
{
    //convert(item);
}

template<class T>
void
syntax_tree_to_string_converter::safe_convert(const boost::optional<T> item)
{
    if(item)
        convert(*item);
}

template<class T, class U>
void
syntax_tree_to_string_converter::safe_convert(const boost::variant<T, U> item)
{
}

}} //namespace socoa::cpp


#undef CONVERT_DECLARATION

#endif
