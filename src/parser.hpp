/*
 * parser.hpp
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

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include "lexer.hpp"

namespace __cfcc {

	typedef class _parser {
		protected:
			lexer _lex;

			void _declaration(void);
			void _declaration_list(void);
			void _special(void);
			void _symbol(void);

		public:
			_parser(void);
			_parser(const std::string &input, bool is_file);
			_parser(const _parser &other);
			virtual ~_parser(void);
			_parser &operator=(const _parser &other);
			void parse(void);
			void reset(void);
	} parser;

};

#endif
