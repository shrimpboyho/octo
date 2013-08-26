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

```c
#include "octo.h"
```

Documentation
-------------
###Get info on a string

```c
size_t len(char* thing);
```
	
Returns the number of characters in ```thing``` excluding the null character.

```c
char charAt(char* s, int n);
```

Returns the character in the string ```s``` at the index of ```n```

##Make an identical copy of a string

```c
char* makeCopy(char* thing);
```

Creates a new copy of ```thing``` in the memory and returns a pointer to it.

##Modify the original string

```c
void* strip(char* thing);
```
	
Trims off both leading and trailing whitespace on ```thing```. It modifies the original buffer.

```c
void* lstrip(char* thing);
```
	
Trims off only the leading whitespace on ```thing```. It modifies the original buffer.

```c
void* rstrip(char* thing);
```
	
Trims off only the trailing whitespace on ```thing```. It modifies the original buffer.

##Create new versions of strings

```c
char* slice(char* thing, int start, int end);
```
	
Creates a new string from ```thing``` that consists of the characters from the starting index (```start```), to the ending index (```end```), and returns a ```char*``` to it. It does not modify the original buffer.
```c
char* replaceBetween(char* s, int start, int end, char* ham);
```

Replaces the content of the string ```s``` between the indexes of ```start``` and ```end``` with the content of the string ```ham```. Returns a pointer to the new buffer.

```c
char* toUpperCase(char* s);
```

Creates a new copy of ```s``` in which all the characters are uppercase and returns a pointer to it.

```c
char* toLowerCase(char* s);
```

Creates a new copy of ```s``` in which all the characters are lowercase and returns a pointer to it.


##Convert between strings and other data types

```c
int stringToInt(char* s);
```

Converts ```s``` to an integer and returns it.

```c
char* intToString(int n);
```

Converts ```n``` to a string and returns a pointer to it.
