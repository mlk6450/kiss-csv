#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "csv.hpp"

#ifndef MULTILINE_SUPPORT
  #define MULTILINE_SUPPORT 1
#endif

CSV::Table::Row::Row(std::string line)
{
  std::string element;

  std::stringstream str(line);

  while (std::getline(str, element, ','))
  {
    elements.push_back(element);
  }
}

std::uint32_t CSV::Table::Row::size()
{
  return elements.size();
}

std::string CSV::Table::Row::get_element(std::uint32_t element_index)
{
  return elements.at(element_index);
}

std::ostream& CSV::Table::Row::print(std::ostream &os)
{
  for(int i=0; i<elements.size(); i++)
  {
    os << elements.at(i);
    if (i < elements.size()-1)
    {
      os << ",";
    }
  }
  os << std::endl;
  return os;
}

std::ostream& CSV::operator<<(std::ostream& os, Table::Row row)
{
  return row.print(os);
}

CSV::Table::Table(std::string fname)
{
  std::fstream file (fname, std::ios::in);
  if (!file.good())
  {
    throw "File does not exist";
  }

  std::string line;
  while (std::getline(file, line))
  {

    #if (MULTILINE_SUPPORT == 1)
      std::string extra;
      // If there is an odd number of '"' then element continues onto next line
      while (std::count(line.begin(), line.end(), '"') % 2)
      {
        std::getline(file, extra);
        line.append("\n");
        line.append(extra);
      }
    #endif

    rows.push_back(Row(line));
  }
}

std::uint32_t CSV::Table::size()
{
  return rows.size();
}

CSV::Table::Row CSV::Table::get_row(std::uint32_t row_index)
{
  return rows.at(row_index);
}

std::string CSV::Table::get_element(std::uint32_t row_index, std::uint32_t element_index)
{
  return get_row(row_index).get_element(element_index);
}

std::ostream& CSV::Table::print(std::ostream& os)
{
  for(int i=0; i<rows.size(); i++)
  {
    os << rows.at(i);
  }
  return os;
}

std::ostream& CSV::operator<<(std::ostream& os, Table table)
{
  return table.print(os);
}
