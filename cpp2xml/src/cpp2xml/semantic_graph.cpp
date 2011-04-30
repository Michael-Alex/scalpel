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

#include "semantic_graph.hpp"
#include <scalpel/utility/variant.hpp>
#include <vector>
#include <sstream>

namespace cpp2xml
{

using namespace detail;

semantic_graph_serializer::semantic_graph_serializer(std::ostream& output):
	output_(output)
{
}

void
semantic_graph_serializer::operator()(const namespace_& entity)
{
	set_ids(entity);
	serialize_namespace(entity);
}

void
semantic_graph_serializer::operator()(const linked_namespace& entity)
{
	set_ids(entity);
	serialize_namespace(entity);
}

void
semantic_graph_serializer::serialize_type
(
	const semantic_entities::type_variant& n,
	const unsigned int indent_level
)
{
	if(auto opt_type = scalpel::utility::get<fundamental_type>(&n))
	{
		output_ << indent(indent_level) << "<fundamental_type type=\"";
		serialize_fundamental_type(*opt_type);
	   	output_ << "\"/>\n";
	}
	else if(const function_type* opt_type = scalpel::utility::get<function_type>(&n))
	{
		serialize_function_type(*opt_type, indent_level);
	}
	else if(auto opt_type = scalpel::utility::get<cv_qualified_type>(&n))
	{
		output_ << indent(indent_level) << "<cv_qualified_type";
		if(opt_type->const_qualified())
			output_ << " const=\"true\"";
		if(opt_type->volatile_qualified())
			output_ << " volatile=\"true\"";
		output_ << ">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</cv_qualified_type>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer>(&n))
	{
		output_ << indent(indent_level) << "<pointer>\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</pointer>\n";
	}
	else if(auto opt_type = scalpel::utility::get<pointer_to_member>(&n))
	{
		output_ << indent(indent_level) << "<pointer_to_member ";
		serialize_class_id_attribute(opt_type->parent_class());
		output_ << ">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</pointer_to_member>\n";
	}
	else if(auto opt_type = scalpel::utility::get<reference>(&n))
	{
		output_ << indent(indent_level) << "<reference>\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</reference>\n";
	}
	else if(auto opt_type = scalpel::utility::get<array>(&n))
	{
		output_ << indent(indent_level) << "<array size=\"" << (*opt_type).size() << "\">\n";
		serialize_type((*opt_type).qualified_type(), indent_level + 1);
		output_ << indent(indent_level) << "</array>\n";
	}
	else if(auto opt_type = scalpel::utility::get<class_*>(&n))
	{
		output_ << indent(indent_level) << "<class id=\"" << get_id(**opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<member_class*>(&n))
	{
		output_ << indent(indent_level) << "<member_class id=\"" << get_id(**opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<union_*>(&n))
	{
		output_ << indent(indent_level) << "<union id=\"" << get_id(**opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<member_union*>(&n))
	{
		output_ << indent(indent_level) << "<member_union id=\"" << get_id(**opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<enum_*>(&n))
	{
		output_ << indent(indent_level) << "<enum id=\"" << get_id(**opt_type) << "\"/>\n";
	}
	else if(auto opt_type = scalpel::utility::get<member_enum*>(&n))
	{
		output_ << indent(indent_level) << "<member_enum id=\"" << get_id(**opt_type) << "\"/>\n";
	}
}

void
semantic_graph_serializer::serialize_fundamental_type
(
	const fundamental_type type
)
{
	std::map<fundamental_type, const char*> fundamental_types_map =
	{
		{fundamental_type::BOOL, "bool"},
		{fundamental_type::CHAR, "char"},
		{fundamental_type::DOUBLE, "double"},
		{fundamental_type::FLOAT, "float"},
		{fundamental_type::INT, "int"},
		{fundamental_type::LONG_DOUBLE, "long double"},
		{fundamental_type::LONG_INT, "long int"},
		{fundamental_type::LONG_LONG_INT, "long long int"},
		{fundamental_type::SHORT_INT, "short int"},
		{fundamental_type::SIGNED_CHAR, "signed char"},
		{fundamental_type::UNSIGNED_CHAR, "unsigned char"},
		{fundamental_type::UNSIGNED_INT, "unsigned int"},
		{fundamental_type::UNSIGNED_LONG_INT, "unsigned long int"},
		{fundamental_type::UNSIGNED_LONG_LONG_INT, "unsigned long long int"},
		{fundamental_type::UNSIGNED_SHORT_INT, "unsigned short int"},
		{fundamental_type::VOID, "void"},
		{fundamental_type::WCHAR_T, "wchar_t"}
	};

	output_ << fundamental_types_map[type];
}

void
semantic_graph_serializer::serialize_base_class
(
	const base_class& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<base_class ";
	serialize_class_id_attribute(entity.base());
	output_ << attribute(entity.access());
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	output_ << "/>\n";
}

void
semantic_graph_serializer::serialize_constructor
(
	const constructor& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<constructor";
	output_ << attribute(entity.access());
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_explicit())
		output_ << " explicit=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</constructor>\n";
}

void
semantic_graph_serializer::serialize_destructor
(
	const destructor& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<destructor";
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level) << "</destructor>\n";
}

void
semantic_graph_serializer::serialize_operator_member_function
(
	const operator_member_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_member_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.overloaded_operator());
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_member_function>\n";
}

void
semantic_graph_serializer::serialize_conversion_function
(
	const conversion_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<conversion_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.access());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	output_ << indent(indent_level) << "</conversion_function>\n";
}

void
semantic_graph_serializer::serialize_simple_member_function
(
	const simple_member_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_member_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << " name=\"" << entity.name() << "\"";
	output_ << attribute(entity.access());
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(entity.is_const())
		output_ << " const=\"true\"";
	if(entity.is_volatile())
		output_ << " volatile=\"true\"";
	if(entity.is_virtual())
		output_ << " virtual=\"true\"";
	if(entity.is_pure())
		output_ << " pure=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</simple_member_function>\n";
}

void
semantic_graph_serializer::serialize_operator_function
(
	const operator_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<operator_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << attribute(entity.overloaded_operator());
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</operator_function>\n";
}

void
semantic_graph_serializer::serialize_simple_function
(
	const simple_function& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<simple_function";
	output_ << " " << id_attribute_to_string(entity);
	output_ << " name=\"" << entity.name() << "\"";
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.is_static())
		output_ << " static=\"true\"";
	if(entity.is_inline())
		output_ << " inline=\"true\"";
	if(!entity.defined())
		output_ << " defined=\"false\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	serialize_function_parameter_list(entity.parameters(), indent_level + 1);

	output_ << indent(indent_level) << "</simple_function>\n";
}

void
semantic_graph_serializer::serialize_function_type
(
	const function_type& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<function_type";
	if(entity.variadic())
		output_ << " variadic=\"true\"";
	if(entity.const_qualified())
		output_ << " const=\"true\"";
	if(entity.volatile_qualified())
		output_ << " volatile=\"true\"";
	output_ << ">\n";

	output_ << indent(indent_level + 1) << "<return_type>\n";
	serialize_type(entity.return_type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</return_type>\n";

	const std::vector<type_variant>& parameter_types = entity.parameter_types();
	output_ << indent(indent_level + 1) << "<parameter_types>\n";
	for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
	{
		const type_variant& type = *i;
		serialize_type(type, indent_level + 2);
	}
	output_ << indent(indent_level + 1) << "</parameter_types>\n";

	output_ << indent(indent_level) << "</function_type>\n";
}

void
semantic_graph_serializer::serialize_function_parameter_list
(
	const function_parameter_list& entity,
	const unsigned int indent_level
)
{
	if(!entity.empty())
	{
		output_ << indent(indent_level) << "<parameters>\n";
		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			serialize_function_parameter(*i, indent_level + 1);
		}
		output_ << indent(indent_level) << "</parameters>\n";
	}
}

void
semantic_graph_serializer::serialize_function_parameter
(
	const function_parameter& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<parameter";
	if(!entity.name().empty())
		output_ << " name=\"" << entity.name() << "\"";
	output_ << ">\n";
	output_ << indent(indent_level + 1) << "<type>\n";
	serialize_type(entity.type(), indent_level + 2);
	output_ << indent(indent_level + 1) << "</type>\n";
	output_ << indent(indent_level) << "</parameter>\n";
}

void
semantic_graph_serializer::serialize_namespace_alias
(
	const namespace_alias& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<namespace_alias";
	output_ << " name=\"" << entity.name() << "\"";
	output_ << " namespace_id=\"" << get_id(entity.referred_namespace()) << "\"";
	output_ << "/>\n";
}



#define serialize_member(TYPE, FUNCTION) \
template<> \
void \
semantic_graph_serializer::serialize_member<semantic_entities::TYPE> \
( \
	const semantic_entities::TYPE& entity, \
	const unsigned int indent_level \
) \
{ \
	FUNCTION(entity, indent_level); \
}

serialize_member(namespace_alias, serialize_namespace_alias)
serialize_member(namespace_, serialize_namespace)
serialize_member(linked_namespace, serialize_namespace)
serialize_member(unnamed_namespace, serialize_unnamed_namespace)
serialize_member(linked_unnamed_namespace, serialize_unnamed_namespace)
serialize_member(class_, serialize_class)
serialize_member(member_class, serialize_class)
serialize_member(union_, serialize_class)
serialize_member(member_union, serialize_class)
serialize_member(enum_, serialize_enum)
serialize_member(member_enum, serialize_enum)
serialize_member(typedef_, serialize_typedef)
serialize_member(member_typedef, serialize_typedef)
serialize_member(constructor, serialize_constructor)
serialize_member(destructor, serialize_destructor)
serialize_member(operator_member_function, serialize_operator_member_function)
serialize_member(conversion_function, serialize_conversion_function)
serialize_member(simple_member_function, serialize_simple_member_function)
serialize_member(operator_function, serialize_operator_function)
serialize_member(simple_function, serialize_simple_function)
serialize_member(variable, serialize_variable)
serialize_member(member_variable, serialize_variable)
serialize_member(bit_field, serialize_variable)

#undef serialize_member



std::string
semantic_graph_serializer::attribute(const member_access& a)
{
	std::ostringstream oss;

	oss << " access=\"";
	switch(a)
	{
		case member_access::PUBLIC:
			oss << "public";
			break;
		case member_access::PROTECTED:
			oss << "protected";
			break;
		case member_access::PRIVATE:
			oss << "private";
			break;
	}
	oss << "\"";

	return oss.str();
}

std::string
semantic_graph_serializer::attribute(const semantic_entities::overloadable_operator op)
{
	std::ostringstream oss;

	oss << " operator=\"";
	switch(op)
	{
		case semantic_entities::overloadable_operator::NEW:
			oss << "new";
			break;
		case semantic_entities::overloadable_operator::NEW_ARRAY:
			oss << "new[]";
			break;
		case semantic_entities::overloadable_operator::DELETE:
			oss << "delete";
			break;
		case semantic_entities::overloadable_operator::DELETE_ARRAY:
			oss << "delete[]";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">>=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<<=";
			break;
		case semantic_entities::overloadable_operator::ARROW_ASTERISK:
			oss << "->*";
			break;
		case semantic_entities::overloadable_operator::PLUS_EQUAL:
			oss << "+=";
			break;
		case semantic_entities::overloadable_operator::MINUS_EQUAL:
			oss << "-=";
			break;
		case semantic_entities::overloadable_operator::ASTERISK_EQUAL:
			oss << "*=";
			break;
		case semantic_entities::overloadable_operator::SLASH_EQUAL:
			oss << "/=";
			break;
		case semantic_entities::overloadable_operator::PERCENT_EQUAL:
			oss << "%=";
			break;
		case semantic_entities::overloadable_operator::CIRCUMFLEX_EQUAL:
			oss << "^=";
			break;
		case semantic_entities::overloadable_operator::AMPERSAND_EQUAL:
			oss << "&=";
			break;
		case semantic_entities::overloadable_operator::PIPE_EQUAL:
			oss << "|=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET:
			oss << "<<";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET:
			oss << ">>";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_EQUAL:
			oss << "==";
			break;
		case semantic_entities::overloadable_operator::EXCLAMATION_EQUAL:
			oss << "!=";
			break;
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL:
			oss << "<=";
			break;
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL:
			oss << ">=";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_AMPERSAND:
			oss << "&&";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_PIPE:
			oss << "||";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_PLUS:
			oss << "++";
			break;
		case semantic_entities::overloadable_operator::DOUBLE_MINUS:
			oss << "--";
			break;
		case semantic_entities::overloadable_operator::ARROW:
			oss << "->";
			break;
		case semantic_entities::overloadable_operator::ROUND_BRACKETS:
			oss << "()";
			break;
		case semantic_entities::overloadable_operator::SQUARE_BRACKETS:
			oss << "[]";
			break;
		case semantic_entities::overloadable_operator::COMMA:
			oss << ",";
			break;
		case semantic_entities::overloadable_operator::PLUS:
			oss << "+";
			break;
		case semantic_entities::overloadable_operator::MINUS:
			oss << "-";
			break;
		case semantic_entities::overloadable_operator::ASTERISK:
			oss << "*";
			break;
		case semantic_entities::overloadable_operator::SLASH:
			oss << "/";
			break;
		case semantic_entities::overloadable_operator::PERCENT:
			oss << "%";
			break;
		case semantic_entities::overloadable_operator::CIRCUMFLEX:
			oss << "^";
			break;
		case semantic_entities::overloadable_operator::AMPERSAND:
			oss << "&";
			break;
		case semantic_entities::overloadable_operator::PIPE:
			oss << "|";
			break;
		case semantic_entities::overloadable_operator::TILDE:
			oss << "~";
			break;
		case semantic_entities::overloadable_operator::EXCLAMATION:
			oss << "!";
			break;
		case semantic_entities::overloadable_operator::EQUAL:
			oss << "=";
			break;
		case semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET:
			oss << "<";
			break;
		case semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET:
			oss << ">";
			break;
	}
	oss << "\"";

	return oss.str();
}

void
semantic_graph_serializer::serialize_class_id_attribute
(
	const scalpel::cpp::semantic_entities::class_ptr_variant& entity
)
{
	if(const class_* const* opt = scalpel::utility::get<class_*>(&entity))
		output_ << " class_id=\"" << get_id(**opt) << "\"";
	else if(const member_class* const* opt = scalpel::utility::get<member_class*>(&entity))
		output_ << " member_class_id=\"" << get_id(**opt) << "\"";
}



#define ENTITY_ID_MAP_OF_TYPE(ENTITY_TYPE, VARIABLE) \
template<> \
typename entity_id_map<ENTITY_TYPE>::type& \
semantic_graph_serializer::entity_id_map_of_type<ENTITY_TYPE>() \
{ \
	return VARIABLE; \
} \
 \
template<> \
const typename entity_id_map<ENTITY_TYPE>::type& \
semantic_graph_serializer::entity_id_map_of_type<ENTITY_TYPE>() const \
{ \
	return VARIABLE; \
}

ENTITY_ID_MAP_OF_TYPE(namespace_, namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(linked_namespace, linked_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(unnamed_namespace, unnamed_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(linked_unnamed_namespace, linked_unnamed_namespace_id_map_)
ENTITY_ID_MAP_OF_TYPE(class_, class_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_class, member_class_id_map_)
ENTITY_ID_MAP_OF_TYPE(union_, union_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_union, member_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_, enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_enum, member_enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(typedef_, typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_typedef, member_typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_member_function, operator_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(conversion_function, conversion_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_member_function, simple_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_function, operator_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_function, simple_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(variable, variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_variable, member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(bit_field, bit_field_id_map_)

#undef ENTITY_ID_MAP_OF_TYPE



void
serialize_semantic_graph
(
	const semantic_graph& graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer(graph);
}

void
serialize_semantic_graph
(
	const linked_semantic_graph& graph,
	std::ostream& output
)
{
	semantic_graph_serializer serializer(output);
	serializer(graph);
}

} //namespace cpp2xml

