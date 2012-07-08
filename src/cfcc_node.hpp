/*
 * cfcc_node.hpp
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

#ifndef CFCC_NODE_HPP_
#define CFCC_NODE_HPP_

#include <string>
#include "cfcc_common.hpp"

namespace __cfcc {

	typedef class _cfcc_node {
		protected:
			size_t _type;

		public:
			_cfcc_node(void);
			_cfcc_node(size_t type);
			_cfcc_node(const _cfcc_node &other);
			virtual ~_cfcc_node(void);
			_cfcc_node &operator=(const _cfcc_node &other);
			size_t get_type(void);
			void set_type(size_t type);
			virtual std::string to_string(void);
			static std::string type_to_string(size_t type);
	} cfcc_node;

};

#endif
