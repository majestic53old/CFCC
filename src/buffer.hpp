/*
 * buffer.hpp
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

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <string>

namespace __cfcc {

	typedef class _buffer {
		protected:
			static const char _NL = '\n';
			static const char _EOS = '\0';

			bool _count;
			long _tln;
			size_t _pos, _ln;
			std::string _buff;

		public:
			_buffer(void);
			_buffer(const std::string &input, bool is_file);
			_buffer(const _buffer &other);
			virtual ~_buffer(void);
			_buffer &operator=(const _buffer &other);
			void clear(void);
			std::string get_buff(void);
			char get_curr(void);
			size_t get_line(void);
			char get_next(void);
			size_t get_pos(void);
			char get_prev(void);
			bool has_prev(void);
			bool has_next(void);
			bool jump(size_t pos);
			void reset(void);
			size_t size(void);
			void toggle_line_count(void);

		friend class _lexer;
	} buffer;

};

#endif
