/*
 * cfcc_syntax_tree.hpp
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

#ifndef CFCC_SYNTAX_TREE_HPP_
#define CFCC_SYNTAX_TREE_HPP_

#include <vector>
#include "cfcc_empty_node.hpp"
#include "cfcc_identifier_node.hpp"
#include "cfcc_special_node.hpp"
#include "cfcc_terminal_node.hpp"

namespace __cfcc {

	typedef class _cfcc_syntax_tree {
		protected:
			_cfcc_terminal_node _comm;
			_cfcc_terminal_node _comm_close;
			_cfcc_terminal_node _comm_open;
			std::vector<_cfcc_identifier_node> _branches;

		public:
			_cfcc_syntax_tree(void);
			_cfcc_syntax_tree(const _cfcc_terminal_node &comm);
			_cfcc_syntax_tree(const _cfcc_terminal_node &comm_close, const _cfcc_terminal_node &comm_open);
			_cfcc_syntax_tree(const _cfcc_terminal_node &comm, const _cfcc_terminal_node &comm_close, const _cfcc_terminal_node &comm_open);
			_cfcc_syntax_tree(const std::vector<_cfcc_identifier_node> &branches);
			_cfcc_syntax_tree(const _cfcc_syntax_tree &other);
			virtual ~_cfcc_syntax_tree(void);
			_cfcc_syntax_tree &operator=(const _cfcc_syntax_tree &other);
			void add_branch(_cfcc_identifier_node &branch);
			void clear(void);
			bool empty(void);
			_cfcc_identifier_node &get_branch(size_t index);
			std::vector<_cfcc_identifier_node> &get_branches(void);
			_cfcc_terminal_node &get_comment(void);
			_cfcc_terminal_node &get_comment_close(void);
			_cfcc_terminal_node &get_comment_open(void);
			bool has_comment(void);
			bool has_comment_close(void);
			bool has_comment_open(void);
			void set_branches(const std::vector<_cfcc_identifier_node> &branches);
			void set_comment(const _cfcc_terminal_node &comm);
			void set_comment_close(const _cfcc_terminal_node &comm_close);
			void set_comment_open(const _cfcc_terminal_node &comm_open);
			size_t size(void);
			std::string to_string(void);
	} cfcc_syntax_tree;

};

#endif
