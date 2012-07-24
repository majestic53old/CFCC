/*
 * cfcc_identifier_node.cpp
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
#include "cfcc_identifier_node.hpp"

using namespace __cfcc;

_cfcc_identifier_node::_cfcc_identifier_node(void) :
		_cfcc_node(NODE_IDENTIFIER) {
	return;
}

_cfcc_identifier_node::_cfcc_identifier_node(const std::string &name) :
		_cfcc_node(NODE_IDENTIFIER), _name(name) {
	return;
}

_cfcc_identifier_node::_cfcc_identifier_node(const _cfcc_identifier_node &other) :
		_name(other._name) {
	_cfcc_node::operator=(other);
}

_cfcc_identifier_node::~_cfcc_identifier_node(void) {
	return;
}

_cfcc_identifier_node &_cfcc_identifier_node::operator=(const _cfcc_identifier_node &other) {
	if(this == &other)
		return *this;
	_name = other._name;
	_cfcc_node::operator=(other);
	return *this;
}

std::string _cfcc_identifier_node::get_name(void) {
	return _name;
}

void _cfcc_identifier_node::set_name(const std::string &name) {
	_name = name;
}

std::string _cfcc_identifier_node::to_string(void) {
	std::stringstream ss;
	ss << "[" << _cfcc_node::to_string() << "]";
	if(!_name.empty())
		ss << " " << _name;
	return ss.str();
}
