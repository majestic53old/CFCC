/*
 * cfcc_syntax_tree.cpp
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
#include "cfcc_syntax_tree.hpp"

using namespace __cfcc;

_cfcc_syntax_tree::_cfcc_syntax_tree(void) {
	return;
}

_cfcc_syntax_tree::_cfcc_syntax_tree(const _cfcc_terminal_node &comm) :
		_comm(comm) {
	return;
}

_cfcc_syntax_tree::_cfcc_syntax_tree(const _cfcc_terminal_node &comm_close, const _cfcc_terminal_node &comm_open) :
		_comm_close(comm_close), _comm_open(comm_open) {
	return;
}

_cfcc_syntax_tree::_cfcc_syntax_tree(const _cfcc_terminal_node &comm, const _cfcc_terminal_node &comm_close, const _cfcc_terminal_node &comm_open) :
		_comm(comm), _comm_close(comm_close), _comm_open(comm_open) {
	return;
}

_cfcc_syntax_tree::_cfcc_syntax_tree(const std::vector<_cfcc_identifier_node> &branches) :
		_branches(branches) {
	return;
}

_cfcc_syntax_tree::_cfcc_syntax_tree(const _cfcc_syntax_tree &other) :
		_comm(other._comm), _comm_close(other._comm_close), _comm_open(other._comm_open), _branches(other._branches) {
	return;
}

_cfcc_syntax_tree::~_cfcc_syntax_tree(void) {
	return;
}

_cfcc_syntax_tree &_cfcc_syntax_tree::operator=(const _cfcc_syntax_tree &other) {
	if(this == &other)
		return *this;
	_comm = other._comm;
	_comm_close = other._comm_close;
	_comm_open = other._comm_open;
	_branches = other._branches;
	return *this;
}

void _cfcc_syntax_tree::add_branch(_cfcc_identifier_node &branch) {
	_branches.push_back(branch);
}

void _cfcc_syntax_tree::clear(void) {
	_branches.clear();
}

bool _cfcc_syntax_tree::empty(void) {
	return _branches.empty();
}

_cfcc_identifier_node &_cfcc_syntax_tree::get_branch(size_t index) {
	return _branches.at(index);
}

std::vector<_cfcc_identifier_node> &_cfcc_syntax_tree::get_branches(void) {
	return _branches;
}

_cfcc_terminal_node &_cfcc_syntax_tree::get_comment(void) {
	return _comm;
}

_cfcc_terminal_node &_cfcc_syntax_tree::get_comment_close(void) {
	return _comm_close;
}

_cfcc_terminal_node &_cfcc_syntax_tree::get_comment_open(void) {
	return _comm_open;
}

bool _cfcc_syntax_tree::has_comment(void) {
	return _comm.is_filled();
}

bool _cfcc_syntax_tree::has_comment_close(void) {
	return _comm_close.is_filled();
}

bool _cfcc_syntax_tree::has_comment_open(void) {
	return _comm_open.is_filled();
}

void _cfcc_syntax_tree::set_branches(const std::vector<_cfcc_identifier_node> &branches) {
	_branches = branches;
}

void _cfcc_syntax_tree::set_comment(const _cfcc_terminal_node &comm) {
	_comm = comm;
}

void _cfcc_syntax_tree::set_comment_close(const _cfcc_terminal_node &comm_close) {
	_comm_close = comm_close;
}

void _cfcc_syntax_tree::set_comment_open(const _cfcc_terminal_node &comm_open) {
	_comm_open = comm_open;
}

size_t _cfcc_syntax_tree::size(void) {
	return _branches.size();
}

std::string _cfcc_syntax_tree::to_string(void) {
	size_t i = 0;
	std::stringstream ss;
	if(has_comment())
		ss << "SINGLE-LINE COMMENT: " << _comm.get_value() << std::endl;
	if(has_comment_open()
			&& has_comment_close())
		ss << "MULTI-LINE COMMENT: " << _comm_open.get_value() << ", " << _comm_close.get_value() << std::endl;
	for(; i < _branches.size(); ++i)
		ss << "\nBRANCH " << (i + 1) << ":" << std::endl << _cfcc_node::node_to_string(&_branches.at(i));
	return ss.str();
}