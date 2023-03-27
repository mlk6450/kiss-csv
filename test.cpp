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
  using namespace CSV;

  // Read csv file
  CSV::Table table = CSV::parseFile("test.csv", ',');
  
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
  for (std::uint32_t row_idx=0; row_idx<table.size(); row_idx++)
  {
    // Get the row
    CSV::Row row = table.at(row_idx);

    // Test if the rows size is correct
    if (row.size() != 3)
    {
      std::cout << "Row " << row_idx << " size is incorrect" << std::endl;
      return -1;
    }

    // Test if each element in the row is correct
    for (std::uint32_t cell_idx=0; cell_idx<row.size(); cell_idx++)
    {
      Cell cell = table.at(row_idx).at(cell_idx);
      if (cell.compare(element_results.at(row_idx).at(cell_idx)))
      {
        std::cout << "Row " << row_idx << " cell " << cell_idx << " is incorrect" << std::endl;
        return -1;
      }
    }

    // Test if the row prints correctly
    std::stringstream ss;
    ss << row;
    std::string row_string = ss.str();    
    if (row_string.compare(print_results.at(row_idx)))
    {
      std::cout << "Row " << row_idx << " prints incorrectly" << std::endl;
      return -1;
    }
  }

  // test adding lines
  std::string newline = "banana,apple,orange";
  table.push_back(parseLine(newline, ','));
  if (  table.at(10).at(0).compare("banana") |
        table.at(10).at(1).compare("apple") |
        table.at(10).at(2).compare("orange") )
  {
    std::cout << "New entry not added correctly" << std::endl;
    return -1;
  }


  // test adding quoted lines
  std::string quotedline = "\"banana,apple,orange\"";
  table.push_back(parseQuotedLine(quotedline, ','));
  if (  table.at(10).at(0).compare("banana") |
        table.at(10).at(1).compare("apple") |
        table.at(10).at(2).compare("orange") )
  {
    std::cout << "New entry not added correctly" << std::endl;
    return -1;
  }

  std::cout << "All tests passed!" << std::endl;

  return 0;
}
