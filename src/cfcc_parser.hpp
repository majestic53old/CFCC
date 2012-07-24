/*
 * cfcc_parser.hpp
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

#ifndef CFCC_PARSER_HPP_
#define CFCC_PARSER_HPP_

#include <string>
#include "cfcc_lexer.hpp"
#include "cfcc_syntax_tree.hpp"

namespace __cfcc {

	typedef class _cfcc_parser {
		protected:
			cfcc_lexer _lex;

			void _declaration(_cfcc_node **node);
			void _declaration_list(_cfcc_node **node);
			void _special(_cfcc_node **node);
			void _symbol(_cfcc_syntax_tree &tree);

		public:
			_cfcc_parser(void);
			_cfcc_parser(const std::string &input, bool is_file);
			_cfcc_parser(const _cfcc_parser &other);
			virtual ~_cfcc_parser(void);
			_cfcc_parser &operator=(const _cfcc_parser &other);
			void parse(_cfcc_syntax_tree &tree);
			void reset(void);
	} cfcc_parser;

};

#endif
