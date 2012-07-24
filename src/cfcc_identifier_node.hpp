/*
 * cfcc_identifier_node.hpp
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

#ifndef CFCC_IDENTIFIER_NODE_HPP_
#define CFCC_IDENTIFIER_NODE_HPP_

#include "cfcc_node.hpp"

namespace __cfcc {

	typedef class _cfcc_identifier_node :
			public _cfcc_node {
		protected:
			std::string _name;

		public:
			_cfcc_identifier_node(void);
			_cfcc_identifier_node(const std::string &name);
			_cfcc_identifier_node(const _cfcc_identifier_node &other);
			virtual ~_cfcc_identifier_node(void);
			_cfcc_identifier_node &operator=(const _cfcc_identifier_node &other);
			std::string get_name(void);
			void set_name(const std::string &name);
			std::string to_string(void);
	} cfcc_identifier_node;

};

#endif
