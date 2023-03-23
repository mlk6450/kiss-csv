# kiss-csv

https://github.com/mlk6450/kiss-csv

## Intro

Keep it simple stupid CSV reader is exactly what it sounds like. It is a simple project that takes the path to a .csv file and populates an easily navigatable table in c++.

Everything in the API should be self explanitory. Below are a few examples:

```C++
// Read .csv table
CSV::Table table = Table("path_to/my.csv");

// Get the length of my table
std::uint32_t length = table.size();

// Read element 0 in row 3
std::string element = table.get_element(3, 0);

// Get the number of elements for row 5
std::uint32_t width = table.get_row(5).size();

// Print the table
std::cout << table;

// Print row 0
std::cout << table.get_row(0);
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

If you want to *really* keep it simple, add the following parameter to the make variable CPPFLAGS "-D MULTILINE_SUPPORT=0". Doing so disables the library's ability to distinguish if a csv element spans multiple lines due to an open paren. This will improve performance slightly and reduce complexity. Note, ./test will fail if this flag is used.
