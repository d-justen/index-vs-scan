#include <cstdlib>
#include <iostream>
#include "Table.hpp"
#include "Scan.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
  size_t num_rows = 1'000'000;
  if (argc > 1) num_rows *= std::atoi(argv[1]);

  auto table = std::make_shared<Table>(num_rows);

  std::cout << "### Scan for values > " << UINT32_MAX / 2 << " ###\n";
  Scan scan(table);
  scan.scan_gt(UINT32_MAX / 2);

  char c = 110;
  std::cout << "\n### Scan for values containing '" << std::string(1, c) << "' ###\n";
  scan.scan_contains_char(c);

  std::cout << "\n### Scan for values > " << UINT32_MAX / 2 << " and containing '" << std::string(1, c) << "' ###\n";
  scan.scan_gt_and_contains(UINT32_MAX / 2, c);
  return 0;
}
