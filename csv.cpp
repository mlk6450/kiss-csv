#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "csv.hpp"

#ifndef QUOTED_MULTILINE_SUPPORT
  #define QUOTED_MULTILINE_SUPPORT 1
#endif

#ifndef QUOTED_DELIMITER_SUPPORT
  #define QUOTED_DELIMITER_SUPPORT 1
#endif

#ifndef COMMENT_LINE_SUPPORT
  #define COMMENT_LINE_SUPPORT 1
#endif

#ifndef BLANK_LINE_SUPPORT
  #define BLANK_LINE_SUPPORT 1
#endif

CSV::Row CSV::parseQuotedLine(const std::string& line, char delimiter)
{
  std::string copy = line;
  std::size_t first = copy.find_first_of("\"");
  std::size_t last = copy.find_last_of("\"");
  copy.erase(last, 1);
  copy.erase(first, 1);

  return parseLine(copy, delimiter);
}

CSV::Row CSV::parseLine(const std::string& line, char delimiter)
{
  Row row;
  std::stringstream ss(line);
  Cell cell;

  while (std::getline(ss, cell, delimiter)) 
  {
    #if (QUOTED_DELIMITER_SUPPORT == 1)
      Cell extra;
      // If there is an odd number of '"' then element continues
      while (std::count(cell.begin(), cell.end(), '"') % 2)
      {
        std::getline(ss, extra, delimiter);
        cell.append(1, delimiter);
        cell.append(extra);
      }
    #endif

    row.push_back(cell);
  }

  return row;
}

CSV::Table CSV::parseFile(const std::string& filename, char delimiter) 
{
  Table table;
  std::ifstream file(filename);

  if (!file.is_open()) 
  {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return table;
  }

  std::string line;
  while (std::getline(file, line)) 
  {
    #if (BLANK_LINE_SUPPORT == 1)
      if (line.length() == 0)
      {
        continue;
      }
    #endif

    #if (COMMENT_LINE_SUPPORT == 1)
      if (line.at(0) == COMMENT_CHARACTER)
      {
        continue;
      }
    #endif

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

    table.push_back(parseLine(line, delimiter));
  }

  file.close();

  return table;
}

std::ostream& CSV::operator<<(std::ostream& os, Row row)
{
  for(int i=0; i<row.size(); i++)
  {
    os << row.at(i);
    if (i < row.size()-1)
    {
      os << ",";
    }
  }
  os << std::endl;

  return os;
}

std::ostream& CSV::operator<<(std::ostream& os, Table table)
{
  for(int i=0; i<table.size(); i++)
  {
    os << table.at(i);
  }
  return os;
}
