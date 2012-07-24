/*
 * cfcc_lexer.cpp
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
#include <stdexcept>
#include "cfcc_lexer.hpp"
#include "cfcc_common.hpp"

using namespace __cfcc;

const std::string _cfcc_lexer::_ASSIGN("=");
const std::string _cfcc_lexer::_EMP("&");
const std::string _cfcc_lexer::_OR("|");

const std::string _cfcc_lexer::_DIRECTIVE[_DIRECTIVE_COUNT] = { "COMMENT", "COMMENT_CLOSE", "COMMENT_OPEN" };
const std::set<std::string> _cfcc_lexer::_DIRECTIVE_SET(_DIRECTIVE, _DIRECTIVE + _DIRECTIVE_COUNT);
const std::string _cfcc_lexer::_SPECIAL[_SPECIAL_COUNT] = { "FLOAT", "INTEGER", "STRING", "STRING_NWS", };
const std::set<std::string> _cfcc_lexer::_SPECIAL_SET(_SPECIAL, _SPECIAL + _SPECIAL_COUNT);
const std::string _cfcc_lexer::_SYMBOL[_SYMBOL_COUNT] = { ">", "]", ")", "<", "[", "(", };
const std::set<std::string> _cfcc_lexer::_SYMBOL_SET(_SYMBOL, _SYMBOL + _SYMBOL_COUNT);

_cfcc_lexer::_cfcc_lexer(void) :
		_type(TYPE_BEGIN) {
	return;
}

_cfcc_lexer::_cfcc_lexer(const std::string &input, bool is_file) :
		_buff(input, is_file), _type(TYPE_BEGIN) {
	return;
}

_cfcc_lexer::_cfcc_lexer(const _cfcc_lexer &other) :
		_buff(other._buff), _type(other._type), _text(other._text) {
	return;
}

_cfcc_lexer::~_cfcc_lexer(void) {
	return;
}

_cfcc_lexer &_cfcc_lexer::operator=(const _cfcc_lexer &other) {
	if(this == &other)
		return *this;
	_buff = other._buff;
	_type = other._type;
	_text = other._text;
	return *this;
}

size_t _cfcc_lexer::_get_directive(void) {
	return _get_type(_text, _DIRECTIVE, _DIRECTIVE_COUNT);
}

size_t _cfcc_lexer::_get_special(void) {
	return _get_type(_text, _SPECIAL, _SPECIAL_COUNT);
}

size_t _cfcc_lexer::_get_symbol(void) {
	return _get_type(_text, _SYMBOL, _SYMBOL_COUNT);
}

size_t _cfcc_lexer::_get_type(const std::string &text, const std::string *types, size_t type_count) {
	size_t pos = 0;
	for(; pos < type_count; ++pos)
		if(types[pos] == text)
			return pos;
	return (size_t) -1;
}

bool _cfcc_lexer::_is_assignment(void) {
	return _text == _ASSIGN;
}

bool _cfcc_lexer::_is_directive(void) {
	return _DIRECTIVE_SET.find(_text) != _DIRECTIVE_SET.end();
}

bool _cfcc_lexer::_is_empty(void) {
	return _text == _EMP;
}

bool _cfcc_lexer::_is_or(void) {
	return _text == _OR;
}

bool _cfcc_lexer::_is_special(void) {
	return _SPECIAL_SET.find(_text) != _SPECIAL_SET.end();
}

bool _cfcc_lexer::_is_symbol(void) {
	return _SYMBOL_SET.find(_text) != _SYMBOL_SET.end();
}

void _cfcc_lexer::_skip_ws(void) {
	if(!_buff.has_next()
			|| (_buff.get_curr() != _COMM
					&& !isspace(_buff.get_curr())))
		return;
	while(_buff.has_next()
			&& isspace(_buff.get_curr()))
		_buff.get_next();
	if(_buff.get_curr() == _COMM)
		while(_buff.has_next()
				&&_buff.get_curr() != _cfcc_buffer::_NL)
			_buff.get_next();
	_skip_ws();
}

size_t _cfcc_lexer::get_line(void) {
	return _buff.get_line();
}

std::string & _cfcc_lexer::get_text(void) {
	return _text;
}

size_t _cfcc_lexer::get_type(void) {
	return _type;
}

bool _cfcc_lexer::has_next(void) {
	return _type != TYPE_END;
}

bool _cfcc_lexer::next(void) {
	_skip_ws();
	_text.clear();
	_type = TYPE_END;
	if(!_buff.has_next())
		return false;
	if(isalpha(_buff.get_curr())) {
		_type = TYPE_IDENTIFIER;
		while(_buff.has_next()
				&& (isalnum(_buff.get_curr())
						|| _buff.get_curr() == _USCORE)) {
			_text += _buff.get_curr();
			_buff.get_next();
		}
		if(_is_directive())
			_type = TYPE_DIRECTIVE;
		else if(_is_special())
			_type = TYPE_SPECIAL;
	} else if(_buff.get_curr() == _TERM) {
		_type = TYPE_TERMINAL;
		if(!_buff.has_next())
			throw std::runtime_error(format_exc(lex_exc_to_string(ERROR_UNTERMINATED_SYMBOL), _buff.get_line()));
		_buff.get_next();
		_buff.toggle_line_count();
		while(_buff.get_curr() != _TERM) {
			if(!_buff.has_next())
				throw std::runtime_error(format_exc(lex_exc_to_string(ERROR_UNTERMINATED_SYMBOL), _buff.get_line()));
			_text += _buff.get_curr();
			_buff.get_next();
		}
		_buff.toggle_line_count();
		if(_buff.has_next())
			_buff.get_next();
	} else {
		_type = TYPE_SYMBOL;
		_text += _buff.get_curr();
		_buff.get_next();
		if(_is_assignment())
			_type = TYPE_ASSIGNMENT;
		else if(_is_empty())
			_type = TYPE_EMPTY;
		else if(_is_or())
			_type = TYPE_OR;
	}
	return true;
}

void _cfcc_lexer::reset(void) {
	_buff.reset();
	_text.clear();
	_type = TYPE_BEGIN;
}

std::string _cfcc_lexer::to_string(void) {
	std::stringstream ss;
	ss << "[" << type_to_string(_type) << "]";
	if(!_text.empty())
		ss << " " << _text;
	return ss.str();
}

std::string _cfcc_lexer::type_to_string(size_t type) {
	std::string output;
	switch(type) {
		case TYPE_ASSIGNMENT: output = "ASSIGNMENT";
			break;
		case TYPE_BEGIN: output = "BEGIN";
			break;
		case TYPE_DIRECTIVE: output = "DIRECTIVE";
			break;
		case TYPE_END: output = "END";
			break;
		case TYPE_EMPTY: output = "EMPTY";
			break;
		case TYPE_IDENTIFIER: output = "IDENTIFIER";
			break;
		case TYPE_OR: output = "OR";
			break;
		case TYPE_SPECIAL: output = "SPECIAL";
			break;
		case TYPE_SYMBOL: output = "SYMBOL";
			break;
		case TYPE_TERMINAL: output = "TERMINAL";
			break;
		default: output = "UNKNOWN";
			break;
	}
	return output;
}
