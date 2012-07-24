/*
 * cfcc_buffer.cpp
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

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "cfcc_buffer.hpp"

using namespace __cfcc;

_cfcc_buffer::_cfcc_buffer(void) :
		_count(true), _tln(0), _pos(0), _ln(1) {
	return;
}

_cfcc_buffer::_cfcc_buffer(const std::string &input, bool is_file) :
		_count(true), _tln(0), _pos(0), _ln(1) {
	if(is_file) {
		std::stringstream ss;
		std::fstream file(input.c_str(), std::ios::in);
		if(!file)
			throw std::runtime_error(input + " (file not found)");
		ss << std::noskipws << file.rdbuf();
		_buff = ss.str();
		file.close();
	} else
		_buff = input;
}

_cfcc_buffer::_cfcc_buffer(const _cfcc_buffer &other) :
		_count(other._count), _tln(other._tln), _pos(other._pos), _ln(other._ln), _buff(other._buff) {
	return;
}

_cfcc_buffer::~_cfcc_buffer(void) {
	return;
}

_cfcc_buffer &_cfcc_buffer::operator=(const _cfcc_buffer &other) {
	if(this == &other)
		return *this;
	_count = other._count;
	_tln = other._tln;
	_pos = other._pos;
	_ln = other._ln;
	_buff = other._buff;
	return *this;
}

void _cfcc_buffer::clear(void) {
	_buff.clear();
	reset();
}

std::string _cfcc_buffer::get_buff(void) {
	return _buff;
}

char _cfcc_buffer::get_curr(void) {
	if(_pos >= _buff.size())
		return _EOS;
	return _buff.at(_pos);
}

size_t _cfcc_buffer::get_line(void) {
	return _ln;
}

char _cfcc_buffer::get_next(void) {
	if(++_pos < _buff.size()
			&& get_curr() == _NL) {
		if(_count)
			++_ln;
		else
			++_tln;
	}
	return get_curr();
}

size_t _cfcc_buffer::get_pos(void) {
	return _pos;
}

char _cfcc_buffer::get_prev(void) {
	if(--_pos > 0
			&& get_curr() == _NL) {
		if(_count)
			--_ln;
		else
			--_tln;
	}
	return get_curr();
}

bool _cfcc_buffer::has_prev(void) {
	return _pos > 0;
}

bool _cfcc_buffer::has_next(void) {
	return _pos < _buff.size();
}

bool _cfcc_buffer::jump(size_t pos) {
	size_t index = _pos;
	if(pos < _buff.size()) {
		for(; index < pos; ++index)
			get_next();
		return true;
	}
	return false;
}

void _cfcc_buffer::reset(void) {
	_count = true;
	_tln = 0;
	_pos = 0;
	_ln = 1;
}

void _cfcc_buffer::set_buff(const std::string &input) {
	_buff = input;
	reset();
}

size_t _cfcc_buffer::size(void) {
	return _buff.size();
}

void _cfcc_buffer::toggle_line_count(void) {
	if(!_count)
		_ln += _tln;
	_tln = 0;
	_count = !_count;
}
