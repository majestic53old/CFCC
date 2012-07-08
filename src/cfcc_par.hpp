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

#ifndef CFCC_PAR_HPP_
#define CFCC_PAR_HPP_

#include <string>
#include "cfcc_lex.hpp"

namespace __cfcc {

	typedef class _cfcc_par {
		protected:
			cfcc_lex _lex;

			void _declaration(void);
			void _declaration_list(void);
			void _special(void);
			void _symbol(void);

		public:
			_cfcc_par(void);
			_cfcc_par(const std::string &input, bool is_file);
			_cfcc_par(const _cfcc_par &other);
			virtual ~_cfcc_par(void);
			_cfcc_par &operator=(const _cfcc_par &other);
			void parse(void);
			void reset(void);
	} cfcc_par;

};

#endif
