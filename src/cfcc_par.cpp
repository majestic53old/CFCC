/*
 * cfcc_par.cpp
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

#include <stdexcept>
#include "cfcc_common.hpp"
#include "cfcc_par.hpp"

using namespace __cfcc;

_cfcc_par::_cfcc_par(void) {
	return;
}

_cfcc_par::_cfcc_par(const std::string &input, bool is_file) :
		_lex(input, is_file) {
	return;
}

_cfcc_par::_cfcc_par(const _cfcc_par &other) :
		_lex(other._lex){
	return;
}

_cfcc_par::~_cfcc_par(void) {
	return;
}

_cfcc_par &_cfcc_par::operator=(const _cfcc_par &other) {
	if(this == &other)
		return *this;
	_lex = other._lex;
	return *this;
}

void _cfcc_par::_declaration(void) {
	size_t sym;
	if(_lex.get_type() == _cfcc_lex::TYPE_SYMBOL) {
		sym = _lex._get_symbol();
		switch(sym) {
			case _cfcc_lex::TYPE_OPEN_IDENTIFIER:
				_lex.next();
				if(_lex.get_type() != _cfcc_lex::TYPE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_IDENTIFIER), _lex.get_line()));
				_lex.next();
				sym = _lex._get_symbol();
				if(sym != _cfcc_lex::TYPE_CLOSE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_BRACKET), _lex.get_line()));
				_lex.next();
				break;
			case _cfcc_lex::TYPE_OPEN_SPECIAL:
				_special();
				break;
			default:
				throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_UNKNOWN_SYMBOL), _lex.get_line()));
				break;
		}
	} else if(_lex.get_type() == _cfcc_lex::TYPE_EMPTY)
		_lex.next();
	else if(_lex.get_type() == _cfcc_lex::TYPE_TERMINAL)
		_lex.next();
	else
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_DECLARATION), _lex.get_line()));
}

void _cfcc_par::_declaration_list(void) {
	_declaration();
	if(!_lex.has_next()
			|| _lex.get_type() == _cfcc_lex::TYPE_DIRECTIVE
			|| _lex.get_type() == _cfcc_lex::TYPE_IDENTIFIER)
		return;
	if(_lex.get_type() == _cfcc_lex::TYPE_OR)
		_lex.next();
	_declaration_list();
}

void _cfcc_par::_special(void) {
	if(_lex.get_type() != _cfcc_lex::TYPE_SYMBOL
			|| _lex._get_symbol() != _cfcc_lex::TYPE_OPEN_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_OPEN_PARENTHESES), _lex.get_line()));
	_lex.next();
	if(_lex.get_type() != _cfcc_lex::TYPE_SPECIAL)
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_SPECIAL), _lex.get_line()));
	_lex.next();
	if(_lex.get_type() != _cfcc_lex::TYPE_SYMBOL
			|| _lex._get_symbol() != _cfcc_lex::TYPE_CLOSE_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_PARENTHESES), _lex.get_line()));
	_lex.next();
}

void _cfcc_par::_symbol(void) {
	size_t type = _lex.get_type();
	switch(type) {
		case _cfcc_lex::TYPE_DIRECTIVE:
		case _cfcc_lex::TYPE_IDENTIFIER:
			_lex.next();
			if(_lex.get_type() != _cfcc_lex::TYPE_ASSIGNMENT)
				throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_ASSIGNMENT), _lex.get_line()));
			_lex.next();
			if(type == _cfcc_lex::TYPE_DIRECTIVE) {
				if(_lex.get_type() != _cfcc_lex::TYPE_TERMINAL)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_TERMINAL), _lex.get_line()));
				_lex.next();
			} else
				_declaration_list();
			break;
		default:
			throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_SYMBOL), _lex.get_line()));
			break;
	}
}

void _cfcc_par::parse(void) {
	_lex.reset();
	_lex.next();
	while(_lex.has_next())
		_symbol();
}

void _cfcc_par::reset(void) {
	_lex.reset();
}
