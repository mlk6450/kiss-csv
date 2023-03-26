#include <sstream>
#include <vector>

#include "csv.hpp"

static const std::vector<std::vector<std::string>> element_results =
{
  {"foo", "bar", "baz"},
  {"foo", "\"bar\"", "baz"},
  {"foo", "\"b\"\"ar\"", "baz"},
  {"foo", "\"b\na\nr\"", "baz"},
  {"foo", "\"\n\nb\n\n\"\"a\"\"\n\nr\n\n\"", "baz"},
  {"foo", "bar", "\"baz\""},
  {"foo", "bar", "\"\"baz\"\""},
  {"foo", "bar", "\"\"\"baz\"\"\""},
  {"foo", "bar", "baz"},
  {"\"f,oo\"", "bar", "\"b,a,z\""}
};

static const std::vector<std::string> print_results =
{
  "foo,bar,baz\n",
  "foo,\"bar\",baz\n",
  "foo,\"b\"\"ar\",baz\n",
  "foo,\"b\na\nr\",baz\n",
  "foo,\"\n\nb\n\n\"\"a\"\"\n\nr\n\n\",baz\n",
  "foo,bar,\"baz\"\n",
  "foo,bar,\"\"baz\"\"\n",
  "foo,bar,\"\"\"baz\"\"\"\n",
  "foo,bar,baz\n",
  "\"f,oo\",bar,\"b,a,z\"\n"
};

int main(int arv, char* argv[])
{
  // Read csv file
  CSV::Table table = CSV::Table("test.csv", ',');
  
  // Print table
  std::cout << "Printing table.." << std::endl;
  std::cout << table;

  // Test for correct table size
  if (table.size() != 10)
  {
    std::cout << "Table size incorrect" << std::endl;
    return -1;
  }

  // For each row...
  for (std::uint32_t row_index=0; row_index<table.size(); row_index++)
  {
    // Get the row
    CSV::Table::Row row = table.at(row_index);

    // Test if the rows size is correct
    if (row.size() != 3)
    {
      std::cout << "Row " << row_index << " size is incorrect" << std::endl;
      return -1;
    }

    // Test if each element in the row is correct
    for (std::uint32_t element_index=0; element_index<row.size(); element_index++)
    {
      std::string element = table.at(row_index, element_index);
      if (element.compare(element_results.at(row_index).at(element_index)))
      {
        std::cout << "Row " << row_index << " element " << element_index << " is incorrect" << std::endl;
        return -1;
      }
    }

    // Test if the row prints correctly
    std::stringstream ss;
    ss << row;
    std::string row_string = ss.str();    
    if (row_string.compare(print_results.at(row_index)))
    {
      std::cout << "Row " << row_index << " prints incorrectly" << std::endl;
      return -1;
    }
  }

  std::cout << "All tests passed!" << std::endl;

  return 0;
}
