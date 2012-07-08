/*
 * cfcc_special_node.hpp
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

#ifndef CFCC_SPECIAL_NODE_HPP_
#define CFCC_SPECIAL_NODE_HPP_

#include <string>
#include "cfcc_node.hpp"

namespace __cfcc {

	typedef class _cfcc_special_node :
			public _cfcc_node {
		protected:
			size_t _special_type;

		public:
			_cfcc_special_node(void);
			_cfcc_special_node(size_t special_type);
			_cfcc_special_node(const _cfcc_special_node &other);
			virtual ~_cfcc_special_node(void);
			_cfcc_special_node &operator=(const _cfcc_special_node &other);
			size_t get_special_type(void);
			void set_special_type(size_t special_type);
			static std::string special_type_to_string(size_t special_type);
			std::string to_string(void);
	} cfcc_special_node;

};

#endif
