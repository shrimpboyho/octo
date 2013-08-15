[octo]() - A String Manipulation Library
========================================
[![Build Status](https://travis-ci.org/shrimpboyho/octo.png)](https://travis-ci.org/shrimpboyho/octo)

A Library for Manipulating Strings in C

How to Install
--------------

First get a copy of the library by git cloning it:

```bash
git clone https://github.com/shrimpboyho/octo.git
cd octo
```

Then you can just include the header file in your code:

```
#include "octo.h"
```

Documentation
-------------

```c
size_t len(char* thing)
```
	
Returns the number of characters in ```thing``` excluding the null character.

```c
char* makeCopy(char* thing)
```
	
Creates a new copy of ```thing``` in the memory and returns a pointer to it.

```c
char* strip(char* thing)
```
	
Trims off both leading and trailing whitespace on ```thing```. It modifies the original buffer.

```c
char* lstrip(char* thing)
```
	
Trims off only the leading whitespace on ```thing```. It modifies the original buffer.

```c
char* rstrip(char* thing)
```
	
Trims off only the trailing whitespace on ```thing```. It modifies the original buffer.

```c
char* slice(char* thing, int start, int end)
```
	
Creates a new string from ```thing``` that consists of the characters from the starting index (```start```), to the ending index (```end```), and returns a ```char*``` to it. It does not modify the original buffer.
	
