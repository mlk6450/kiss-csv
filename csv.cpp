#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "csv.hpp"

#ifndef QUOTED_MULTILINE_SUPPORT
  #define QUOTED_MULTILINE_SUPPORT 1
#endif

#ifndef QUOTED_DELIMITER_SUPPORT
  #define QUOTED_DELIMITER_SUPPORT 1
#endif

CSV::Table::Row::Row(std::string line, char delimiter)
{
  std::string element;

  std::stringstream str(line);

  while (std::getline(str, element, delimiter))
  {
    #if (QUOTED_DELIMITER_SUPPORT == 1)
      std::string extra;
      // If there is an odd number of '"' then element continues
      while (std::count(element.begin(), element.end(), '"') % 2)
      {
        std::getline(str, extra, delimiter);
        element.append(1, delimiter);
        element.append(extra);
      }
    #endif
    elements.push_back(element);
  }
}

std::uint32_t CSV::Table::Row::size()
{
  return elements.size();
}

std::string CSV::Table::Row::at(std::uint32_t element_index)
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

CSV::Table::Table(std::string fname, char delimiter)
{
  std::fstream file (fname, std::ios::in);
  if (!file.good())
  {
    throw "File does not exist";
  }

  std::string line;
  while (std::getline(file, line))
  {

    #if (QUOTED_MULTILINE_SUPPORT == 1)
      std::string extra;
      // If there is an odd number of '"' then line continues onto next line of the file
      while (std::count(line.begin(), line.end(), '"') % 2)
      {
        std::getline(file, extra);
        line.append("\n");
        line.append(extra);
      }
    #endif

    rows.push_back(Row(line, delimiter));
  }
}

std::uint32_t CSV::Table::size()
{
  return rows.size();
}

CSV::Table::Row CSV::Table::at(std::uint32_t row_index)
{
  return rows.at(row_index);
}

std::string CSV::Table::at(std::uint32_t row_index, std::uint32_t element_index)
{
  return at(row_index).at(element_index);
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
