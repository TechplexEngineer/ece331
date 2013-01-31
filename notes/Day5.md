Title: Day 5
Date: 1/29/13
Published: true

## Questions on hw2
mmap is a confusing function, which has 6 Args: 
-	NULL
-	pagesize
-	set protection read only
-	flags to sared map
-	file descriptor from dev mem
-	set offset

It returns a pointer in our address space, so we can index into it


## Make and RegularExpressions (below)

### Sample Makefile
	TARGET=vcopy
	OBJS=vcopy.o support.o
	CFLAGS=-g -Wall -O2
	LIBS=-ldvdnav -ldvdread

	.PHONY: clean

	TARGET: ${OBJS}
    ${CC} -o ${TARGET} ${OBJS} ${LIBS}

	clean:
    ${RM} *.o core*

	vcopy.o: vcopy.h support.h
	support.o: support.h

@note: use `#` to comment in makefiles

### Format:
	target ... : prerequisites ...
    recipe
    ...

@note: MUST use tabs to indent recipes 

### Lots of implicit rules
`$ make -p` //get a listing of implicit rules

#### Example implicit rule:
	%.o: %.c
    $(COMPILE.c) $(OUTPUT_OPTIONS) $<

### Variables
syntax:
VARIABLE=value

#### Predefined Variables
CFLAGS, CC, FC, LD, AR, AS, F77FLAGS, LDFLAGS

### Standard Targets:

1. all				//build entire project
2. install		//push generated code to target
3. uninstall	//clear target
4. clean			//remove generated files

## RegularExpressions
>A regular expression is a specific pattern that provides concise and flexible means to "match" (specify and recognize) strings of text, such as particular characters, words, or patterns of characters  [@wikipedia](http://en.wikipedia.org/wiki/Regular_expression)

### Meta characters: 
1. \
1. ^
1. .
1. $
1. |
1. ()
1. []

### Quantifiers: 
1. *
1. +
1. ?
1. {n}
1. {n,}
1. {n,m}

@note: paraphrased from: [@regular-expressions.info](http://www.regular-expressions.info/quickstart.html)

### Character Class (Character Sets)
1. A "character class" matches only one out of several characters.
1. You can use a hyphen inside a character class to specify a range of characters.
1. Typing a caret after the opening square bracket will match any character that is not in the character class. (negate the character class)

### Shorthand Character Classes (Recommend not using these)
1. `\d` matches a single character that is a digit
1. `\w` matches a "word character" (alphanumeric characters plus underscore)
1. `\s` matches a whitespace character (includes tabs and line breaks)

@note: Shorthand matching varies by implementation

### Non-Printable Characters
1. `\t` to match a tab character (ASCII 0x09)
1. `\r` for carriage return (0x0D)
1. `\n` for line feed (0x0A)
1. `\xFF` to match a specific character by its hexadecimal index in the character set
1. `\uFFFF` to insert a Unicode character (where Unicode is supported)

@note: All non-printable characters can be used directly in the regular expression, or as part of a character class.

### The `.` dot matches (almost) all
The dot matches a single character, except line break characters.

@note: Use the dot sparingly. Often, a character class or negated character class is faster and more precise.

### Anchors
Anchors do not match any characters. They match a position.
1. `^` matches at the start of the string
1. `$` matches at the end of the string

### Quantifiers / Repetition
1. `?` makes the preceding token in the regular expression optional
1. `*` attempt to match the preceding token zero or more times
1. `+` attempt to match the preceding token once or more
1. `{5}` preceding token exactly 5 times 
1. `{5,}` preceding token 5 or more times
1. `{min,max}` preceding token min to max times. (inclusive)