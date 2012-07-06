/*
 * parser.cpp
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

#include <iostream>

#include <stdexcept>
#include "parser.hpp"
#include "shared.hpp"

using namespace __cfcc;

_parser::_parser(void) {
	return;
}

_parser::_parser(const std::string &input, bool is_file) :
		_lex(input, is_file) {
	return;
}

_parser::_parser(const _parser &other) :
		_lex(other._lex){
	return;
}

_parser::~_parser(void) {
	return;
}

_parser &_parser::operator=(const _parser &other) {
	if(this == &other)
		return *this;
	_lex = other._lex;
	return *this;
}

void _parser::_declaration(void) {
	size_t sym;
	if(_lex.get_type() == _lexer::TYPE_SYMBOL) {
		sym = _lex._get_symbol();
		switch(sym) {
			case _lexer::TYPE_OPEN_IDENTIFIER:
				_lex.next();
				if(_lex.get_type() != _lexer::TYPE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_IDENTIFIER), _lex.get_line()));
				_lex.next();
				sym = _lex._get_symbol();
				if(sym != _lexer::TYPE_CLOSE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_BRACKET), _lex.get_line()));
				_lex.next();
				break;
			case _lexer::TYPE_OPEN_SPECIAL:
				_special();
				break;
			default:
				throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_UNKNOWN_SYMBOL), _lex.get_line()));
				break;
		}
	} else if(_lex.get_type() == _lexer::TYPE_EMPTY)
		_lex.next();
	else if(_lex.get_type() == _lexer::TYPE_TERMINAL)
		_lex.next();
	else
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_DECLARATION), _lex.get_line()));
}

void _parser::_declaration_list(void) {
	_declaration();
	if(!_lex.has_next()
			|| _lex.get_type() == _lexer::TYPE_DIRECTIVE
			|| _lex.get_type() == _lexer::TYPE_IDENTIFIER)
		return;
	if(_lex.get_type() == _lexer::TYPE_OR)
		_lex.next();
	_declaration_list();
}

void _parser::_special(void) {
	if(_lex.get_type() != _lexer::TYPE_SYMBOL
			|| _lex._get_symbol() != _lexer::TYPE_OPEN_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_OPEN_PARENTHESES), _lex.get_line()));
	_lex.next();
	if(_lex.get_type() != _lexer::TYPE_SPECIAL)
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_SPECIAL), _lex.get_line()));
	_lex.next();
	if(_lex.get_type() != _lexer::TYPE_SYMBOL
			|| _lex._get_symbol() != _lexer::TYPE_CLOSE_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_PARENTHESES), _lex.get_line()));
	_lex.next();
}

void _parser::_symbol(void) {
	size_t type = _lex.get_type();
	switch(type) {
		case _lexer::TYPE_DIRECTIVE:
		case _lexer::TYPE_IDENTIFIER:
			_lex.next();
			if(_lex.get_type() != _lexer::TYPE_ASSIGNMENT)
				throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_ASSIGNMENT), _lex.get_line()));
			_lex.next();
			if(type == _lexer::TYPE_DIRECTIVE) {
				if(_lex.get_type() != _lexer::TYPE_TERMINAL)
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

void _parser::parse(void) {
	_lex.reset();
	_lex.next();
	while(_lex.has_next())
		_symbol();
}

void _parser::reset(void) {
	_lex.reset();
}
