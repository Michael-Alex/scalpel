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



semantic_graph_serializer::serialize_type_visitor::serialize_type_visitor
(
	semantic_graph_serializer& serializer,
	const unsigned int indent_level
):
	serializer_(serializer),
	output_(serializer_.output_),
	indent_level_(indent_level)
{
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const fundamental_type& type)
{
	output_ << indent(indent_level_) << "<fundamental_type type=\"";
	serializer_.serialize_fundamental_type(type);
	output_ << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const function_type& type)
{
	serializer_.serialize_function_type(type, indent_level_);
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const cv_qualified_type& type)
{
	output_ << indent(indent_level_) << "<cv_qualified_type";
	if(type.const_qualified())
		output_ << " const=\"true\"";
	if(type.volatile_qualified())
		output_ << " volatile=\"true\"";
	output_ << ">\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</cv_qualified_type>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer& type)
{
	output_ << indent(indent_level_) << "<pointer>\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</pointer>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const pointer_to_member& type)
{
	output_ << indent(indent_level_) << "<pointer_to_member ";
	serializer_.serialize_class_id_attribute(type.parent_class());
	output_ << ">\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</pointer_to_member>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const reference& type)
{
	output_ << indent(indent_level_) << "<reference>\n";
	serializer_.serialize_type((type).qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</reference>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const array& type)
{
	output_ << indent(indent_level_) << "<array size=\"" << type.size() << "\">\n";
	serializer_.serialize_type(type.qualified_type(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</array>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const class_* type)
{
	output_ << indent(indent_level_) << "<class id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_class* type)
{
	output_ << indent(indent_level_) << "<member_class id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const union_* type)
{
	output_ << indent(indent_level_) << "<union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_union* type)
{
	output_ << indent(indent_level_) << "<member_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_union* type)
{
	output_ << indent(indent_level_) << "<anonymous_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const anonymous_member_union* type)
{
	output_ << indent(indent_level_) << "<anonymous_member_union id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const enum_t* type)
{
	output_ << indent(indent_level_) << "<enum id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type_visitor::operator()(const member_enum_t* type)
{
	output_ << indent(indent_level_) << "<member_enum id=\"" << serializer_.get_id(*type) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_type
(
	const semantic_entities::type_t& n,
	const unsigned int indent_level
)
{
	serialize_type_visitor visitor(*this, indent_level);
	apply_visitor(visitor, n);
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

	const std::vector<type_t>& parameter_types = entity.parameter_types();
	output_ << indent(indent_level + 1) << "<parameter_types>\n";
	for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
	{
		const type_t& type = *i;
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

namespace
{

#define EXPRESSION_TYPE(TYPE, STR) \
std::string \
operator()(const TYPE) \
{ \
	return #STR; \
}

	struct: scalpel::utility::static_visitor<std::string>
	{
		EXPRESSION_TYPE(prefix_increment_expression, prefix_increment)
		EXPRESSION_TYPE(prefix_decrement_expression, prefix_decrement)
		EXPRESSION_TYPE(indirection_expression, indirection)
		EXPRESSION_TYPE(pointer_expression, pointer)
		EXPRESSION_TYPE(negation_expression, negation)
		EXPRESSION_TYPE(logical_negation_expression, logical_negation)
		EXPRESSION_TYPE(complement_expression, complement)
		EXPRESSION_TYPE(multiplication_expression, multiplication)
		EXPRESSION_TYPE(division_expression, division)
		EXPRESSION_TYPE(modulo_expression, modulo)
		EXPRESSION_TYPE(addition_expression, addition)
		EXPRESSION_TYPE(subtraction_expression, subtraction)
		EXPRESSION_TYPE(left_shift_expression, left_shift)
		EXPRESSION_TYPE(right_shift_expression, right_shift)
		EXPRESSION_TYPE(less_than_expression, less_than)
		EXPRESSION_TYPE(less_than_or_equal_to_expression, less_than_or_equal_to)
		EXPRESSION_TYPE(greater_than_expression, greater_than)
		EXPRESSION_TYPE(greater_than_or_equal_to_expression, greater_than_or_equal_to)
		EXPRESSION_TYPE(equal_to_expression, equal_to)
		EXPRESSION_TYPE(not_equal_to_expression, not_equal_to)
		EXPRESSION_TYPE(bitwise_and_expression, bitwise_and)
		EXPRESSION_TYPE(bitwise_exclusive_or_expression, bitwise_exclusive_or)
		EXPRESSION_TYPE(bitwise_inclusive_or_expression, bitwise_inclusive_or)
		EXPRESSION_TYPE(logical_and_expression, logical_and)
		EXPRESSION_TYPE(logical_or_expression, logical_or)
		EXPRESSION_TYPE(conditional_expression, conditional)
		EXPRESSION_TYPE(assignment_expression, assignment)
		EXPRESSION_TYPE(multiplication_assignment_expression, multiplication_assignment)
		EXPRESSION_TYPE(division_assignment_expression, division_assignment)
		EXPRESSION_TYPE(modulo_assignment_expression, modulo_assignment)
		EXPRESSION_TYPE(addition_assignment_expression, addition_assignment)
		EXPRESSION_TYPE(subtraction_assignment_expression, subtraction_assignment)
		EXPRESSION_TYPE(left_shift_assignment_expression, left_shift_assignment)
		EXPRESSION_TYPE(right_shift_assignment_expression, right_shift_assignment)
		EXPRESSION_TYPE(bitwise_and_assignment_expression, bitwise_and_assignment)
		EXPRESSION_TYPE(bitwise_exclusive_or_assignment_expression, bitwise_exclusive_or_assignment)
		EXPRESSION_TYPE(bitwise_inclusive_or_assignment_expression, bitwise_inclusive_or_assignment)

		EXPRESSION_TYPE(conversion_to_bool, conversion_to_bool)
		EXPRESSION_TYPE(conversion_to_int, conversion_to_int)
		EXPRESSION_TYPE(conversion_to_long_int, conversion_to_long_int)
		EXPRESSION_TYPE(conversion_to_unsigned_int, conversion_to_unsigned_int)
		EXPRESSION_TYPE(conversion_to_unsigned_long_int, conversion_to_unsigned_long_int)
		EXPRESSION_TYPE(conversion_to_float, conversion_to_float)
		EXPRESSION_TYPE(conversion_to_double, conversion_to_double)
		EXPRESSION_TYPE(conversion_to_long_double, conversion_to_long_double)

		EXPRESSION_TYPE(variable*, variable)
		EXPRESSION_TYPE(enum_constant<int>*, int_enum_constant)
		EXPRESSION_TYPE(enum_constant<unsigned int>*, unsigned_int_enum_constant)
		EXPRESSION_TYPE(enum_constant<long int>*, long_int_enum_constant)
		EXPRESSION_TYPE(enum_constant<unsigned long int>*, unsigned_long_int_enum_constant)

		EXPRESSION_TYPE(bool, bool)
		EXPRESSION_TYPE(char, char)
		EXPRESSION_TYPE(wchar_t, wchar_t)
		EXPRESSION_TYPE(int, int)
		EXPRESSION_TYPE(long int, long int)
		EXPRESSION_TYPE(long long int, long long int)
		EXPRESSION_TYPE(unsigned int, unsigned int)
		EXPRESSION_TYPE(unsigned long int, unsigned long int)
		EXPRESSION_TYPE(unsigned long long int, unsigned long long int)
		EXPRESSION_TYPE(float, float)
		EXPRESSION_TYPE(double, double)
		EXPRESSION_TYPE(long double, long double)
		EXPRESSION_TYPE(std::string, string)
		EXPRESSION_TYPE(std::wstring, wide string)
	} get_expression_type_visitor;

#undef EXPRESSION_TYPE
}



semantic_graph_serializer::serialize_expression_visitor::serialize_expression_visitor
(
	semantic_graph_serializer& serializer,
	const unsigned int indent_level
):
	serializer_(serializer),
	output_(serializer_.output_),
	indent_level_(indent_level)
{
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const T t)
{
	output_ << indent(indent_level_) << t << '\n';
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const unary_expression<Tag>& operation)
{
	output_ << indent(indent_level_) << "<operand>\n";
	serializer_.serialize_expression(operation.operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</operand>\n";
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const binary_expression<Tag>& operation)
{
	output_ << indent(indent_level_) << "<left_operand>\n";
	serializer_.serialize_expression(operation.left_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</left_operand>\n";
	output_ << indent(indent_level_) << "<right_operand>\n";
	serializer_.serialize_expression(operation.right_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</right_operand>\n";
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conditional_expression& operation)
{
	output_ << indent(indent_level_) << "<condition_operand>\n";
	serializer_.serialize_expression(operation.condition_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</condition_operand>\n";
	output_ << indent(indent_level_) << "<true_operand>\n";
	serializer_.serialize_expression(operation.true_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</true_operand>\n";
	output_ << indent(indent_level_) << "<false_operand>\n";
	serializer_.serialize_expression(operation.false_operand(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</false_operand>\n";
}

template<int Tag>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(const conversion<Tag>& conv)
{
	output_ << indent(indent_level_) << "<source_value>\n";
	serializer_.serialize_expression(conv.source_value(), indent_level_ + 1);
	output_ << indent(indent_level_) << "</source_value>\n";
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(variable* const& v)
{
	output_ << indent(indent_level_) << "<variable id=\"" << serializer_.get_id(*v) << "\"/>\n";
}

template<typename T>
void
semantic_graph_serializer::serialize_expression_visitor::operator()(enum_constant<T>* const constant)
{
	output_ << indent(indent_level_) << "<enum_constant id=\"" << serializer_.get_id(*constant) << "\"/>\n";
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const char c)
{
	output_ << indent(indent_level_) << static_cast<int>(c) << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const bool b)
{
	output_ << indent(indent_level_) << (b ? "true" : "false") << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::string& str)
{
	output_ << indent(indent_level_);
	output_ << std::hex;
	for(char c: str)
		output_ << (static_cast<int>(c) & 0xff) << ' ';
	output_ << std::dec;
	output_ << '\n';
}

void
semantic_graph_serializer::serialize_expression_visitor::operator()(const std::wstring& str)
{
	output_ << indent(indent_level_);
	output_ << std::hex;
	for(wchar_t c: str)
		output_ << static_cast<int>(c) << ' ';
	output_ << std::dec;
	output_ << '\n';
}



void
semantic_graph_serializer::serialize_expression
(
	const semantic_entities::expression_t& entity,
	const unsigned int indent_level
)
{
	output_ << indent(indent_level) << "<expression";
	output_ << " type=\"" << apply_visitor(get_expression_type_visitor, entity) << "\"";
	output_ << ">\n";

	serialize_expression_visitor visitor(*this, indent_level + 1);
	apply_visitor(visitor, entity);

	output_ << indent(indent_level) << "</expression>\n";
}



#define SERIALIZE_MEMBER(TYPE, FUNCTION) \
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

SERIALIZE_MEMBER(namespace_alias, serialize_namespace_alias)
SERIALIZE_MEMBER(namespace_, serialize_namespace)
SERIALIZE_MEMBER(linked_namespace, serialize_namespace)
SERIALIZE_MEMBER(unnamed_namespace, serialize_unnamed_namespace)
SERIALIZE_MEMBER(linked_unnamed_namespace, serialize_unnamed_namespace)
SERIALIZE_MEMBER(class_, serialize_class)
SERIALIZE_MEMBER(member_class, serialize_class)
SERIALIZE_MEMBER(union_, serialize_class)
SERIALIZE_MEMBER(member_union, serialize_class)
SERIALIZE_MEMBER(anonymous_union, serialize_class)
SERIALIZE_MEMBER(anonymous_member_union, serialize_class)
SERIALIZE_MEMBER(enum_t, serialize_enum)
SERIALIZE_MEMBER(member_enum_t, serialize_enum)
SERIALIZE_MEMBER(typedef_, serialize_typedef)
SERIALIZE_MEMBER(member_typedef, serialize_typedef)
SERIALIZE_MEMBER(constructor, serialize_constructor)
SERIALIZE_MEMBER(destructor, serialize_destructor)
SERIALIZE_MEMBER(operator_member_function, serialize_operator_member_function)
SERIALIZE_MEMBER(conversion_function, serialize_conversion_function)
SERIALIZE_MEMBER(simple_member_function, serialize_simple_member_function)
SERIALIZE_MEMBER(operator_function, serialize_operator_function)
SERIALIZE_MEMBER(simple_function, serialize_simple_function)
SERIALIZE_MEMBER(variable, serialize_variable)
SERIALIZE_MEMBER(member_variable, serialize_variable)
SERIALIZE_MEMBER(static_member_variable, serialize_variable)
SERIALIZE_MEMBER(bit_field, serialize_variable)

#undef SERIALIZE_MEMBER



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
ENTITY_ID_MAP_OF_TYPE(anonymous_union, anonymous_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(anonymous_member_union, anonymous_member_union_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_t, enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_enum_t, member_enum_id_map_)
ENTITY_ID_MAP_OF_TYPE(typedef_, typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_typedef, member_typedef_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_member_function, operator_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(conversion_function, conversion_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_member_function, simple_member_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(operator_function, operator_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(simple_function, simple_function_id_map_)
ENTITY_ID_MAP_OF_TYPE(variable, variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(member_variable, member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(static_member_variable, static_member_variable_id_map_)
ENTITY_ID_MAP_OF_TYPE(bit_field, bit_field_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<int>, int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<unsigned int>, unsigned_int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<long int>, long_int_enum_constant_id_map_)
ENTITY_ID_MAP_OF_TYPE(enum_constant<unsigned long int>, unsigned_long_int_enum_constant_id_map_)

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

