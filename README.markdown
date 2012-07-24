CFCC
========

A context-free language parser generator written in C++.

1. [Purpose](https://github.com/majestic53/CFCC#purpose)
2. [Syntax](https://github.com/majestic53/CFCC#syntax)
5. [Building the Library](https://github.com/majestic53/CFCC#building-the-library)
	* [Windows](https://github.com/majestic53/CFCC#windows)
	* [Linux/Unix](https://github.com/majestic53/CFCC#linux-unix)
6. [Using the Library](https://github.com/majestic53/CFCC#using-the-library)
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
<assignment> ::= '='

<comment> ::= '#'

<empty> ::= '&'

<declaration> ::= '<' <identifier> '>' | <special> | <terminal> | <empty>

<declaration_list> ::= '(' <declaration_list> ')' | <declaration> <declaration_list> | <declaration> <or> <declaration_list> | <declaration>

<directive> ::= COMMENT | COMMENT_OPEN | COMMENT_CLOSE

<identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*

<or> ::= '|'

<special> ::= '[' <special_type> ']'

<special_type> ::= FLOAT | INTEGER | STRING | STRING_NWS

<symbol> ::= <identifier> <assignment> <declaration_list> | <directive> <assignment> <terminal>

<terminal> ::= '\'' .* '\''
```

###How About a Quick Example

With this grammar it is easy to define various languages. For example, a simplified xml language can be defined like so:
```
# XML 1.0 Spec (w/out xml declarations, namespaces. etc.)

COMMENT_CLOSE = '-->'

COMMENT_OPEN = '<!--'

attribute = <identifier> '="' (STRING) '"'

attribute_list = <attribute> <attribute_list> | &

identifier = (STRING_NWS)

node = '<' <identifier> <attribute_list> <node_end> | &

node_end = '/>' | '>' <element> '</' <identifier> '>'

node_list = <node> <node_list> | &

element = <node_list> | (STRING)
```

Building the Library
======

There are two ways to use CLCC. You can choose to compile it as a static library or simply include the files in your own project.

###Windows:

Import files into a Visual Studios solution, or create a new static library solution to build the project as a .lib file.

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

Using the Library
======

To use CFCC as a static library, simply include the library in your project with the appropriate linker flag:
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

###Verifying a Language Definition

To verify a language definition, instantiate a CFCC parser object and run the ```par.parse();``` member routine (see below). At the moment, this process only checks for correct syntax, not semantics. This routine outputs a syntax tree, but it isn't used at this point. You can print the contents of the tree by calling ```tree.to_string();```.

```cpp
#include <iostream>
#include <stdexcept>
#include "[path-to-headers]/cfcc_parser.hpp"
#include "[path-to-headers]/cfcc_syntax_tree.hpp"

using namespace __cfcc;

int main(void) {

	cfcc_parser par;
	cfcc_syntax_tree tree;
	std::string path = "[path-to-language-definition]";

	try {

		// instantiate parser object
		par = cfcc_parser(path, true);

		// attempt to parse file
		par.parse(tree);

		// if you want to print the contents of the tree
		// std::cout << tree.to_string() << std::endl;
	} catch(std::runtime_error &exc) {

		// an exception occurred
		std::cerr << "Exception: " << exc.what() << std::endl;
		std::cout << path << " is NOT valid." << std::endl;
		return 1;
	}

	// file has valid CFCC syntax
	std::cout << path << " is valid!" << std::endl;
	return 0;
}
```

More examples will be posted as the project progresses.

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
