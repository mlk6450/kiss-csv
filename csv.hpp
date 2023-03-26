#ifndef CSV_TABLE_HPP_
#define CSV_TBALE_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace CSV
{
  typedef std::string Cell;
  typedef std::vector<Cell> Row;
  typedef std::vector<Row> Table;

  Row parseLine(const std::string& line, char delimiter);
  Table parseFile(const std::string& filename, char delimiter);

  std::ostream& operator<<(std::ostream& os, Row row);
  std::ostream& operator<<(std::ostream& os, Table table);
}

#endif /* CSV_TABLE_HPP_ */
