#ifndef CSV_TABLE_HPP_
#define CSV_TBALE_HPP_

#include <string>
#include <vector>
#include <iostream>

#define DEFUALT_DELIMITER (',')

namespace CSV
{
  typedef std::string Cell;
  typedef std::vector<Cell> Row;
  typedef std::vector<Row> Table;

  Row parseQuotedLine(const std::string& line, char delimiter = DEFUALT_DELIMITER);
  Row parseLine(const std::string& line, char delimiter = DEFUALT_DELIMITER);
  Table parseFile(const std::string& filename, char delimiter = DEFUALT_DELIMITER);

  std::ostream& operator<<(std::ostream& os, Row row);
  std::ostream& operator<<(std::ostream& os, Table table);
}

#endif /* CSV_TABLE_HPP_ */
