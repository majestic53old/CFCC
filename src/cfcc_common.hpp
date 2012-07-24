/*
 * cfcc_common.hpp
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

#ifndef CFCC_COMMON_HPP_
#define CFCC_COMMON_HPP_

#include <string>

namespace __cfcc {

	enum DIRECTIVE_TYPE {
		DIRECTIVE_COMMENT = 0,
		DIRECTIVE_COMMENT_CLOSE,
		DIRECTIVE_COMMENT_OPEN,
	};

	enum NODE_TYPE {
		NODE_EMPTY = 0,
		NODE_GENERIC,
		NODE_IDENTIFIER,
		NODE_SPECIAL,
		NODE_TERMINAL,
	};

	enum LEX_EXC {
		ERROR_UNTERMINATED_SYMBOL = 0,
	};

	enum PARSER_EXC {
		ERROR_EXPECTING_ASSIGNMENT = 0,
		ERROR_EXPECTING_CLOSE_BRACKET,
		ERROR_EXPECTING_CLOSE_PARENTHESES,
		ERROR_EXPECTING_CLOSE_NESTING,
		ERROR_EXPECTING_DECLARATION,
		ERROR_EXPECTING_IDENTIFIER,
		ERROR_EXPECTING_OPEN_PARENTHESES,
		ERROR_EXPECTING_SPECIAL,
		ERROR_EXPECTING_SYMBOL,
		ERROR_EXPECTING_TERMINAL,
		ERROR_UNKNOWN_DECLARATION,
		ERROR_UNKNOWN_SYMBOL,
		ERROR_COMMENT_REDECLARATION,
		ERROR_INTERNAL_NULL_NODE,
		ERROR_INTERNAL_ALLOC_FAIL,
	};

	enum SPECIAL_NODE_TYPE {
		NODE_SPECIAL_FLOAT = 0,
		NODE_SPECIAL_GENERIC,
		NODE_SPECIAL_INTEGER,
		NODE_SPECIAL_STRING,
		NODE_SPECIAL_STRING_NWS,
	};

	std::string format_exc(const std::string &exc_mess);
	std::string format_exc(const std::string &exc_mess, size_t line);
	std::string format_exc(const std::string &mess, const std::string &exc_mess, size_t line);
	std::string lex_exc_to_string(size_t type);
	std::string parser_exc_to_string(size_t type);
};

#endif
