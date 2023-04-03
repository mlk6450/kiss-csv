# kiss-csv

https://github.com/mlk6450/kiss-csv

## Intro

Keep it simple stupid CSV reader is exactly what it sounds like. It is a simple project that takes the path to a .csv file and populates an easily navigatable table in c++.

Everything in the API should be self explanitory. Below are a few examples:

```C++
// Namespace must be included to support << override
using namespace CSV;

// Read .csv table
CSV::Table table = parseFile("path_to/my.csv", ',');

// Get the length of my table
std::uint32_t length = table.size();

// Read row 3 element 0
std::string element = table.at(3).at(0);

// Get the number of elements for row 5
std::uint32_t width = table.at(5).size();

// Print the table
std::cout << table;

// Print row 0
std::cout << table.at(0);
```

## Building

The provided Makefile includes all neccessary build targets. These include:

```bash
# Build the library libcsv.a
make lib 

# Build the test file
make test

# Build library and install it to /usr/local
sudo make install

# Uninstall from /usr/local
sudo make uninstall

# Delete output products
make clean

# Delete auto generated dependency file (could be needed if source files are added/removed)
make distclean
```

## Notes

If you want to *really* keep it simple, add a combination of the following parameters to the make variable CPPFLAGS:

* "-D QUOTED_MULTILINE_SUPPORT=0"
* "-D QUOTED_DELIMITER_SUPPORT=0"
* "-D COMMENT_LINE_SUPPORT=0"
* "-D BLANK_LINE_SUPPORT=0"
 
QUOTED_MULTILINE_SUPPORT=0 disables the library's ability to distinguish if a csv line spans multiple lines in the source file due to a paren escaped element. 

QUOTED_DELIMITER_SUPPORT=0 disables the library's ability to distinguish if a csv element contains an paren escaped dilimiter character.

COMMENT_LINE_SUPPORT=0 disables the library's abilty to distinguish if a line is a comment (meaning the first character is the COMMENT_CHARACTER).

BLANK_LINE_SUPPORT=0 disables the library's ability to distinguish if a line is blank. It is not recomended to disable this feature. If a blank line is encountered when this is disabled the library will core dump.

Adding any of these flag (especially the first two) will slightly improve performance and reduce complexity. But NOTE, ./test will fail if they are used because the provided testing program tests all of these features.
