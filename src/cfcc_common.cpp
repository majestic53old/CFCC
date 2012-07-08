/*
 * cfcc_common.cpp
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
#include "cfcc_common.hpp"

namespace __cfcc {

	std::string format_exc(const std::string &exc_mess, size_t line) {
		return format_exc("", exc_mess, line);
	}

	std::string format_exc(const std::string &mess, const std::string &exc_mess, size_t line) {
		std::stringstream ss;
		ss << "ln. " << line << ": " << exc_mess;
		if(!mess.empty())
			ss << ": " << mess;
		return ss.str();
	}

	std::string lex_exc_to_string(size_t type) {
		std::string output;
		switch(type) {
			case ERROR_UNTERMINATED_SYMBOL: output = "Unterminated symbol";
				break;
			default: output = "Unknown exception";
				break;
		}
		return output;
	}

	std::string parser_exc_to_string(size_t type) {
		std::string output;
		switch(type) {
			case ERROR_EXPECTING_ASSIGNMENT: output = "Expecting assignment";
				break;
			case ERROR_EXPECTING_CLOSE_BRACKET: output = "Expecting close bracket";
				break;
			case ERROR_EXPECTING_CLOSE_PARENTHESES: output = "Expecting close parentheses";
				break;
			case ERROR_EXPECTING_DECLARATION: output = "Expecting declaration";
				break;
			case ERROR_EXPECTING_IDENTIFIER: output = "Expecting identifer";
				break;
			case ERROR_EXPECTING_OPEN_PARENTHESES: output = "Expecting open parentheses";
				break;
			case ERROR_EXPECTING_SPECIAL: output = "Expecting special declaration (FLOAT, INTEGER, or STRING)";
				break;
			case ERROR_EXPECTING_SYMBOL: output = "Expecting identifier or directive";
				break;
			case ERROR_EXPECTING_TERMINAL: output = "Expecting terminal";
				break;
			case ERROR_UNKNOWN_SYMBOL: output = "Unknown symbol";
				break;
			default: output = "Unknown exception";
				break;
		}
		return output;
	}

};
