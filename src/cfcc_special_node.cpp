/*
 * cfcc_special_node.cpp
 * Copyright (C) 2012 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "cfcc_special_node.hpp"

using namespace __cfcc;

_cfcc_special_node::_cfcc_special_node(void) :
		_cfcc_node(NODE_SPECIAL) {
	return;
}

_cfcc_special_node::_cfcc_special_node(size_t special_type) :
		_cfcc_node(NODE_SPECIAL), _special_type(special_type) {
	return;
}

_cfcc_special_node::_cfcc_special_node(const _cfcc_special_node &other) :
		_cfcc_node(NODE_SPECIAL), _special_type(other._special_type) {
	return;
}

_cfcc_special_node::~_cfcc_special_node(void) {
	return;
}

_cfcc_special_node &_cfcc_special_node::operator=(const _cfcc_special_node &other) {
	if(this == &other)
		return *this;
	_special_type = other._special_type;
	return *this;
}

size_t _cfcc_special_node::get_special_type(void) {
	return _special_type;
}

void _cfcc_special_node::set_special_type(size_t special_type) {
	_special_type = special_type;
}

std::string _cfcc_special_node::special_type_to_string(size_t special_type) {
	std::string output;
	switch(special_type) {
		case NODE_SPECIAL_FLOAT: output = "FLOAT";
			break;
		case NODE_SPECIAL_GENERIC: output = "GENERIC";
			break;
		case NODE_SPECIAL_INTEGER: output = "INTEGER";
			break;
		case NODE_SPECIAL_STRING: output = "STRING";
			break;
		case NODE_SPECIAL_STRING_NWS: output = "STRING NWS";
			break;
		default: output = "UNKNOWN";
			break;
	}
	return output;
}

std::string _cfcc_special_node::to_string(void) {
	std::stringstream ss;
	ss << "[" << cfcc_node::type_to_string(NODE_SPECIAL) << "] " << special_type_to_string(_special_type);
	return ss.str();
}
