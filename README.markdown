CFCC
========

A context-free language parser generator written in C++.

1. [Purpose](https://github.com/majestic53/CFCC#purpose)
2. [Syntax](https://github.com/majestic53/CFCC#syntax)
5. [Build](https://github.com/majestic53/CFCC#build)
	* [Windows](https://github.com/majestic53/CFCC#windows)
	* [Linux/Unix](https://github.com/majestic53/CFCC#linux-unix)
6. [Using This Library](https://github.com/majestic53/CFCC#using-this-library)
7. [Examples](https://github.com/majestic53/CFCC#examples)
8. [License](https://github.com/majestic53/CFCC#license)

Purpose
========

The goal of this project is to create a library that can quickly and easily generate parsers for context-free languages. Specifically, parsers that can be created and used in real-time applications from user-specified language definitions.

Syntax
======

The syntax used by CFCC is similar to Backus-Normal Form (BNF) in many ways. However, CFCC has added special types for representing floating-point values, integer values, and strings (both with and without whitespace). CFCC also supports both single-line and multi-line comment declarations.

The BNF grammar used by CFCC is listed below (begins at symbol):
```
<comment> ::= '#'

<empty> ::= '&'

<declaration> ::= '<' <identifier> '>' | <special> | <terminal> | <empty>

<declaration_list> ::= <declaration> <declaration_list> | <declaration> <or> <declaration_list> | <declaration>

<directive> ::= COMMENT | COMMENT_OPEN | COMMENT_CLOSE

<identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*

<or> ::= '|'

<special> ::= '(' <special_type> ')'

<special_type> ::= FLOAT | INTEGER | STRING | STRING_NWS

<symbol> ::= <identifier> '=' <declaration_list> | <directive> '=' <terminal>

<terminal> ::= '\'' .* '\''
```

With this grammar it is easy to define various languages. For example, a simplified xml language can be defined like so:
```
# XML 1.0 Spec (w/out xml declarations)

COMMENT_CLOSE = '-->'

COMMENT_OPEN = '<!--'

attribute = <identifier> '=' '"' (STRING) '"'

attribute_list = <attribute> <attribute_list> | &

identifier = (STRING_NWS)

node = '<' <identifier> <attribute_list> <node_end> | &

node_end = '/>' | '>' <element> '</' <identifier> '>'

node_list = <node> <node_list> | &

element = <node_list> | (STRING)
```

Build
======

###Windows:

This project has not been tested in a Windows environment. However, the files should be able to be imported into a Visual Studios project without a problem.

###Linux/Unix:

Using the makefile to generate a static library (libcfcc.a)

Requirements (tested with):
* g++ 4.6 or newer (or any compiler with c++0x compliance)
* make 3.8 or newer

For Debian:
```
sudo apt-get install build-essential make
```

Build:
```
make
```

Clean:
```
make clean
```

Using This Library
======

To use CFCC, simply include the library in your project with the appropriate linker flag:
```
-lcfcc
```

Make sure to include the header files and indicate the namespace  in your project as well:
```cpp
#include "[path-to-headers]/[header].hpp"
...

using namespace __cfcc;
```

Examples
======

Examples will be posted when the project is closer to being finished.

License
======

Copyright(C) 2012 David Jolly <majestic53@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
