/*
 * cfcc_empty_node.hpp
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

#ifndef CFCC_EMPTY_NODE_HPP_
#define CFCC_EMPTY_NODE_HPP_

#include <string>
#include "cfcc_node.hpp"

namespace __cfcc {

	typedef class _cfcc_empty_node :
			public _cfcc_node {
		public:
			_cfcc_empty_node(void);
			virtual ~_cfcc_empty_node(void);
			std::string to_string(void);
	} cfcc_empty_node;

};

#endif
