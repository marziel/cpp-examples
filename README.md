# cpp-examples
C++ code snippets demonstrating modern and/or non-obvious languge features.

* **call_once**: usage of *std::once_flag*
* **compile_time_exp2**: computing powers of 2 at compile time
* **concepts**: usage of Concepts TS
* **copy_swap_idiom**: the idiom explained, an important caveat noticed
* **delegates_freestanding**: delegates for free-standing functions
* **delegates_methods**: maybe hazardous but a very robust hack for implementing class methods delegates
* **exceptions_in_initlist**: using exceptions in constructor's initialisation list
* **extra_parentheses**: meanings of extra parentheses explained and also the NRVO shown
* **inline_asm**: brief GCC's inline assembly demonstration and explanation
* **intseq**: usage of *std::integer_sequence* and related stuff
* **iterate_enum_class**: easy iterating over enum class's members
* **mixin**: mixin design pattern showcase
* **naked_asm**: usage of 'naked' assembly code from C++
* **nested_exc**: usage of nested exceptions
* **odr_violation**: a nasty exaple of 'One-Definition Rule' violation
* **optional_and_concepts**: usage of *std::optional* and, by the way, Concepts TS
* **param_pack_expansion**: folding/expanding template parameter packs
* **pointer_to_field**: usage of pointers to class's fields, some explanations about offsets and struct sizing
* **prioritised_overload**: how to make an uniform interface to several methods chosen (prioritised) by number
* **uncaught_exc**: usage of *std::uncaught_exceptions*

Compile with attached CMake scripts using *g++*. Some examples can be compiled with *clang++* as well.
