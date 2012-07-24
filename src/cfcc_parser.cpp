/*
 * cfcc_parser.cpp
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
#include "cfcc_parser.hpp"

using namespace __cfcc;

_cfcc_parser::_cfcc_parser(void) {
	return;
}

_cfcc_parser::_cfcc_parser(const std::string &input, bool is_file) :
		_lex(input, is_file) {
	return;
}

_cfcc_parser::_cfcc_parser(const _cfcc_parser &other) :
		_lex(other._lex){
	return;
}

_cfcc_parser::~_cfcc_parser(void) {
	return;
}

_cfcc_parser &_cfcc_parser::operator=(const _cfcc_parser &other) {
	if(this == &other)
		return *this;
	_lex = other._lex;
	return *this;
}

void _cfcc_parser::_declaration(_cfcc_node **node) {
	size_t sym;
	if(_lex.get_type() == _cfcc_lexer::TYPE_SYMBOL) {
		sym = _lex._get_symbol();
		switch(sym) {
			case _cfcc_lexer::TYPE_OPEN_IDENTIFIER:
				_lex.next();
				if(_lex.get_type() != _cfcc_lexer::TYPE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_IDENTIFIER), _lex.get_line()));
				(*node) = new _cfcc_identifier_node(_lex.get_text());
				if(!(*node))
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_ALLOC_FAIL)));
				(*node)->set_filled(true);
				_lex.next();
				sym = _lex._get_symbol();
				if(sym != _cfcc_lexer::TYPE_CLOSE_IDENTIFIER)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_BRACKET), _lex.get_line()));
				_lex.next();
				break;
			case _cfcc_lexer::TYPE_OPEN_SPECIAL:
				_special(node);
				break;
			default:
				throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_UNKNOWN_SYMBOL), _lex.get_line()));
				break;
		}
	} else if(_lex.get_type() == _cfcc_lexer::TYPE_EMPTY) {
		(*node) = new _cfcc_empty_node;
		if(!(*node))
			throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_ALLOC_FAIL)));
		(*node)->set_filled(true);
		_lex.next();
	} else if(_lex.get_type() == _cfcc_lexer::TYPE_TERMINAL) {
		(*node) = new _cfcc_terminal_node(_lex.get_text());
		if(!(*node))
			throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_ALLOC_FAIL)));
		(*node)->set_filled(true);
		_lex.next();
	} else
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_DECLARATION), _lex.get_line()));
}

void _cfcc_parser::_declaration_list(_cfcc_node **node) {
	if(!(*node))
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_NULL_NODE)));
	if(_lex.get_type() == _cfcc_lexer::TYPE_SYMBOL
			&& _lex._get_symbol() == _cfcc_lexer::TYPE_OPEN_NESTING) {
		_lex.next();
		_declaration_list(node);
		if(_lex.get_type() != _cfcc_lexer::TYPE_SYMBOL
				|| _lex._get_symbol() != _cfcc_lexer::TYPE_CLOSE_NESTING)
			throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_NESTING), _lex.get_line()));
		_lex.next();
	} else {
		_cfcc_node *dec_node = NULL;
		_declaration(&dec_node);
		if(!dec_node)
			throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_NULL_NODE)));
		(*node)->add_child(dec_node);
		if(!_lex.has_next()
				|| _lex.get_type() == _cfcc_lexer::TYPE_DIRECTIVE
				|| _lex.get_type() == _cfcc_lexer::TYPE_IDENTIFIER
				|| _lex._get_symbol() == _cfcc_lexer::TYPE_CLOSE_NESTING) {
			(*node)->set_finish(true);
			return;
		}
		if(_lex.get_type() == _cfcc_lexer::TYPE_OR) {
			_lex.next();
			_declaration_list(node);
		} else
			_declaration_list(&dec_node);
	}
}

void _cfcc_parser::_special(_cfcc_node **node) {
	if(_lex.get_type() != _cfcc_lexer::TYPE_SYMBOL
			|| _lex._get_symbol() != _cfcc_lexer::TYPE_OPEN_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_OPEN_PARENTHESES), _lex.get_line()));
	_lex.next();
	if(_lex.get_type() != _cfcc_lexer::TYPE_SPECIAL)
		throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_SPECIAL), _lex.get_line()));
	(*node) = new _cfcc_special_node(_lex._get_special());
	if(!(*node))
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_ALLOC_FAIL)));
	(*node)->set_filled(true);
	_lex.next();
	if(_lex.get_type() != _cfcc_lexer::TYPE_SYMBOL
			|| _lex._get_symbol() != _cfcc_lexer::TYPE_CLOSE_SPECIAL)
		throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_CLOSE_PARENTHESES), _lex.get_line()));
	_lex.next();
}

void _cfcc_parser::_symbol(_cfcc_syntax_tree &tree) {
	size_t type = _lex.get_type(),
			dir_type = _lex._get_directive();
	_cfcc_identifier_node ident(_lex.get_text());
	switch(type) {
		case _cfcc_lexer::TYPE_DIRECTIVE:
		case _cfcc_lexer::TYPE_IDENTIFIER:
			_lex.next();
			if(_lex.get_type() != _cfcc_lexer::TYPE_ASSIGNMENT)
				throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_ASSIGNMENT), _lex.get_line()));
			_lex.next();
			if(type == _cfcc_lexer::TYPE_DIRECTIVE) {
				if(_lex.get_type() != _cfcc_lexer::TYPE_TERMINAL)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_EXPECTING_TERMINAL), _lex.get_line()));
				switch(dir_type) {
					case _cfcc_lexer::TYPE_COMMENT:
						if(tree.get_comment().is_filled())
							throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_COMMENT_REDECLARATION), _lex.get_line()));
						tree.get_comment().set_value(_lex.get_text());
						tree.get_comment().set_filled(true);
						break;
					case _cfcc_lexer::TYPE_COMMENT_CLOSE:
						if(tree.get_comment_close().is_filled())
							throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_COMMENT_REDECLARATION), _lex.get_line()));
						tree.get_comment_close().set_value(_lex.get_text());
						tree.get_comment_close().set_filled(true);
						break;
					case _cfcc_lexer::TYPE_COMMENT_OPEN:
						if(tree.get_comment_open().is_filled())
							throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_COMMENT_REDECLARATION), _lex.get_line()));
						tree.get_comment_open().set_value(_lex.get_text());
						tree.get_comment_open().set_filled(true);
						break;
					default:
						throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_UNKNOWN_DECLARATION), _lex.get_line()));
						break;
				}
				_lex.next();
			} else {
				_cfcc_node *node = &ident;
				_declaration_list(&node);
				if(!node)
					throw std::runtime_error(format_exc(parser_exc_to_string(ERROR_INTERNAL_NULL_NODE)));
				ident.set_filled(true);
				tree.add_branch(ident);
			}
			break;
		default:
			throw std::runtime_error(format_exc(_lex.get_text(), parser_exc_to_string(ERROR_EXPECTING_SYMBOL), _lex.get_line()));
			break;
	}
}

void _cfcc_parser::parse(_cfcc_syntax_tree &tree) {
	_lex.reset();
	_lex.next();
	while(_lex.has_next())
		_symbol(tree);
}

void _cfcc_parser::reset(void) {
	_lex.reset();
}
