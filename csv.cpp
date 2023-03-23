#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "csv.hpp"

CSV::Table::Row::Row()
{

}

void CSV::Table::Row::push_back(std::string element)
{
  elements.push_back(element);
}

std::ostream &CSV::Table::Row::print(std::ostream &os)
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

  std::string line, element;
  while (std::getline(file, line))
  {
    Row row = Row();
    std::stringstream str(line);

    while (std::getline(str, element, ','))
    {
      row.push_back(element);
    }
    rows.push_back(row);
  }
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

int main(int arv, char* argv[])
{
  CSV::Table table = CSV::Table("test.csv");

  std::cout << table;

  return 0;
}
