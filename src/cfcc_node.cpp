/*
 * cfcc_node.cpp
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

#include "cfcc_node.hpp"

using namespace __cfcc;

_cfcc_node::_cfcc_node(void) :
		_type(NODE_GENERIC) {
	return;
}

_cfcc_node::_cfcc_node(size_t type) :
		_type(type) {
	return;
}

_cfcc_node::_cfcc_node(const _cfcc_node &other) :
		_type(other._type) {
	return;
}

_cfcc_node::~_cfcc_node(void) {
	return;
}

_cfcc_node &_cfcc_node::operator=(const _cfcc_node &other) {
	if(this == &other)
		return *this;
	_type = other._type;
	return *this;
}

size_t _cfcc_node::get_type(void) {
	return _type;
}

void _cfcc_node::set_type(size_t type) {
	_type = type;
}

std::string _cfcc_node::to_string(void) {
	return this->to_string();
}

std::string _cfcc_node::type_to_string(size_t type) {
	std::string output;
	switch(type) {
		case NODE_EMPTY: output = "EMPTY NODE";
			break;
		case NODE_GENERIC: output = "GENERIC NODE";
			break;
		case NODE_IDENTIFIER: output = "IDENTIFIER NODE";
			break;
		case NODE_SPECIAL: output = "SPECIAL NODE";
			break;
		case NODE_SYMBOL: output = "SYMBOL NODE";
			break;
		case NODE_TERMINAL: output = "TERMINAL NODE";
			break;
		default: output = "UNKNOWN NODE";
			break;
	}
	return output;
}
