/*
 * lexer.hpp
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

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <set>
#include <string>
#include "buffer.hpp"

namespace __cfcc {

	typedef class _lexer {
		protected:
			static const char _COMM = '#';
			static const char _TERM = '\'';
			static const char _USCORE = '_';
			static const std::string _ASSIGN;
			static const std::string _EMP;
			static const std::string _OR;

			static const size_t _DIRECTIVE_COUNT = 3;
			static const std::string _DIRECTIVE[_DIRECTIVE_COUNT];
			static const std::set<std::string> _DIRECTIVE_SET;
			static const size_t _SPECIAL_COUNT = 4;
			static const std::string _SPECIAL[_SPECIAL_COUNT];
			static const std::set<std::string> _SPECIAL_SET;
			static const size_t _SYMBOL_COUNT = 4;
			static const std::string _SYMBOL[_SYMBOL_COUNT];
			static const std::set<std::string> _SYMBOL_SET;

			buffer _buff;
			size_t _type;
			std::string _text;

			std::string _format_exc(size_t type);
			std::string _format_exc(const std::string &mess, size_t type);
			size_t _get_directive(void);
			size_t _get_special(void);
			size_t _get_symbol(void);
			size_t _get_type(const std::string &text, const std::string *types, size_t type_count);
			bool _is_assignment(void);
			bool _is_directive(void);
			bool _is_empty(void);
			bool _is_or(void);
			bool _is_special(void);
			bool _is_symbol(void);
			void _skip_ws(void);

		public:

			enum LEX_DIREC_TYPE {
				TYPE_COMMENT,
				TYPE_COMMENT_CLOSE,
				TYPE_COMMENT_OPEN,
			};

			enum LEX_EXC {
				ERROR_UNTERMINATED_SYMBOL,
			};

			enum LEX_TYPE {
				TYPE_ASSIGNMENT,
				TYPE_BEGIN,
				TYPE_DIRECTIVE,
				TYPE_END,
				TYPE_EMPTY,
				TYPE_IDENTIFIER,
				TYPE_OR,
				TYPE_SPECIAL,
				TYPE_SYMBOL,
				TYPE_TERMINAL,
			};

			enum LEX_SPEC_TYPE {
				TYPE_FLOAT,
				TYPE_INTEGER,
				TYPE_STRING,
				TYPE_STRING_NWS,
			};

			enum LEX_SYM_TYPE {
				TYPE_CLOSE_IDENTIFIER,
				TYPE_CLOSE_SPECIAL,
				TYPE_OPEN_IDENTIFIER,
				TYPE_OPEN_SPECIAL,
			};

			_lexer(void);
			_lexer(const std::string &input, bool is_file);
			_lexer(const _lexer &other);
			virtual ~_lexer(void);
			_lexer &operator=(const _lexer &other);
			static std::string exc_to_string(size_t type);
			size_t get_line(void);
			std::string &get_text(void);
			size_t get_type(void);
			bool has_next(void);
			bool next(void);
			void reset(void);
			std::string to_string(void);
			static std::string type_to_string(size_t type);
	} lexer;

};

#endif
