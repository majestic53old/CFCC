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

#include <queue>
#include <sstream>
#include <stdexcept>
#include "cfcc_node.hpp"

using namespace __cfcc;

_cfcc_node::_cfcc_node(void) :
		_finish(false), _filled(false), _type(NODE_GENERIC) {
	return;
}

_cfcc_node::_cfcc_node(size_t type) :
		_finish(false), _filled(false), _type(type) {
	return;
}

_cfcc_node::_cfcc_node(size_t type, bool finish) :
		_finish(finish), _filled(false), _type(type) {
	return;
}

_cfcc_node::_cfcc_node(size_t type, bool finish, const std::vector<_cfcc_node *> &children) :
		_finish(finish), _filled(false), _type(type), _children(children) {
	return;
}

_cfcc_node::_cfcc_node(const _cfcc_node *other) :
		_finish(other->_finish), _filled(other->_filled), _type(other->_type), _children(other->_children) {
	return;
}

_cfcc_node::_cfcc_node(const _cfcc_node &other) :
		_finish(other._finish), _filled(other._filled), _type(other._type), _children(other._children) {
	return;
}

_cfcc_node::~_cfcc_node(void) {
	return;
}

_cfcc_node &_cfcc_node::operator=(const _cfcc_node &other) {
	if(this == &other)
		return *this;
	_finish = other._finish;
	_filled = other._filled;
	_type = other._type;
	_children = other._children;
	return *this;
}

void _cfcc_node::_cleanup_helper(_cfcc_node *node) {
	size_t i = 0;
	for(; i < node->size(); ++i)
		_cleanup_helper(node->get_child_at(i));
	delete node;
}

void _cfcc_node::add_child(_cfcc_node *child) {
	_children.push_back(child);
}

void _cfcc_node::cleanup(void) {
	size_t i = 0;
	for(; i < size(); ++i)
		_cleanup_helper(_children.at(i));
}

void _cfcc_node::clear(void) {
	cleanup();
}

bool _cfcc_node::empty(void) {
	return _children.empty();
}

_cfcc_node *_cfcc_node::get_child_at(size_t index) {
	return _children.at(index);
}

std::vector<_cfcc_node *> &_cfcc_node::get_children(void) {
	return _children;
}

size_t _cfcc_node::get_type(void) {
	return _type;
}

bool _cfcc_node::is_filled(void) {
	return _filled;
}

bool _cfcc_node::is_finish(void) {
	return _finish;
}

std::string _cfcc_node::node_to_string(_cfcc_node *root) {
	size_t i;
	std::stringstream ss;
	std::queue<_cfcc_node *> que;
	if(!root)
		return "Empty";
	que.push(root);
	while(!que.empty()) {
		_cfcc_node *curr = que.front();
		que.pop();
		ss << curr->to_string() << std::endl;
		for(i = 0; i < curr->size(); ++i)
			que.push(curr->get_child_at(i));
	}
	return ss.str();
}

void _cfcc_node::set_filled(bool filled) {
	_filled = filled;
}

void _cfcc_node::set_finish(bool finish) {
	_finish = finish;
}

void _cfcc_node::set_type(size_t type) {
	_type = type;
}

size_t _cfcc_node::size(void) {
	return _children.size();
}

std::string _cfcc_node::to_string(void) {
	return type_to_string(_type);
}

std::string _cfcc_node::type_to_string(size_t type) {
	std::string output;
	switch(type) {
		case NODE_EMPTY: output = "EMPTY";
			break;
		case NODE_GENERIC: output = "GENERIC";
			break;
		case NODE_IDENTIFIER: output = "IDENTIFIER";
			break;
		case NODE_SPECIAL: output = "SPECIAL";
			break;
		case NODE_TERMINAL: output = "TERMINAL";
			break;
		default: output = "UNKNOWN";
			break;
	}
	return output;
}
