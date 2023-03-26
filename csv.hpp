#ifndef CSV_TABLE_HPP_
#define CSV_TBALE_HPP_

#include <string>
#include <vector>
#include <iostream>

namespace CSV
{
  class Table
  {
  public:
    class Row
    {
    private:
      std::vector<std::string> elements;
    public:
      Row(std::string line, char delimiter);

      std::uint32_t size();
      std::string at(std::uint32_t element_index);

      std::ostream& print(std::ostream& os);
    };

  private:
    std::vector<Row> rows;

  public:
    Table(std::string fname, char delimiter);

    std::uint32_t size();
    Row at(std::uint32_t row_index);
    std::string at(std::uint32_t row_index, std::uint32_t element_index);

    std::ostream& print(std::ostream& os);
  };

  std::ostream& operator<<(std::ostream& os, Table::Row row);
  std::ostream& operator<<(std::ostream& os, Table table);
}

#endif /* CSV_TABLE_HPP_ */
