#include <cstdlib>
#include <iostream>
#include "Table.hpp"
#include "Scan.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
  size_t num_rows = 1'000'000;
  if (argc > 1) num_rows *= std::atoi(argv[1]);

  const auto table = std::make_shared<Table>(num_rows);

  const auto gt = UINT32_MAX / 2;
  char c = 110;

  Scan scan(table);

  scan.scan_gt(gt);
  scan.scan_contains_char(c);
  scan.scan_gt_and_contains(gt, c);

  return 0;
}
