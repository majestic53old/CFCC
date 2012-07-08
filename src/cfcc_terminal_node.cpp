/*
 * cfcc_terminal_node.cpp
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
#include "cfcc_terminal_node.hpp"

using namespace __cfcc;

_cfcc_terminal_node::_cfcc_terminal_node(void) :
		_cfcc_node(NODE_TERMINAL) {
	return;
}

_cfcc_terminal_node::_cfcc_terminal_node(const std::string &value) :
		_cfcc_node(NODE_TERMINAL), _value(value) {
	return;
}

_cfcc_terminal_node::_cfcc_terminal_node(const _cfcc_terminal_node &other) :
		_cfcc_node(NODE_TERMINAL), _value(other._value) {
	return;
}

_cfcc_terminal_node &_cfcc_terminal_node::operator=(const _cfcc_terminal_node &other) {
	if(this == &other)
		return *this;
	_value = other._value;
	return *this;
}

_cfcc_terminal_node::~_cfcc_terminal_node(void) {
	return;
}

std::string _cfcc_terminal_node::get_value(void) {
	return _value;
}

void _cfcc_terminal_node::set_value(const std::string &value) {
	_value = value;
}

std::string _cfcc_terminal_node::to_string(void) {
	std::stringstream ss;
	ss << "[" << cfcc_node::type_to_string(NODE_IDENTIFIER) << "]";
	if(!_value.empty())
		ss << " " << _value;
	return ss.str();
}
