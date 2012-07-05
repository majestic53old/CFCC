/*
 * shared.hpp
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

#ifndef SHARED_HPP_
#define SHARED_HPP_

#include <string>

namespace __cfcc {

	enum LEX_EXC {
		ERROR_UNTERMINATED_SYMBOL,
	};

	enum PARSER_EXC {
		ERROR_EXPECTING_ASSIGNMENT,
		ERROR_EXPECTING_CLOSE_BRACKET,
		ERROR_EXPECTING_CLOSE_PARENTHESES,
		ERROR_EXPECTING_IDENTIFIER,
		ERROR_EXPECTING_OPEN_PARENTHESES,
		ERROR_EXPECTING_SPECIAL,
		ERROR_EXPECTING_SYMBOL,
		ERROR_EXPECTING_TERMINAL,
		ERROR_UNKNOWN_SYMBOL,
	};

	std::string format_exc(const std::string &exc_mess, size_t line);
	std::string format_exc(const std::string &mess, const std::string &exc_mess, size_t line);
	std::string lex_exc_to_string(size_t type);
	std::string parser_exc_to_string(size_t type);
};

#endif
