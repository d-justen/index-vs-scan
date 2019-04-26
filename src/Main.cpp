#include <iostream>
#include "Table.hpp"
#include "Scan.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
    auto table = std::make_shared<Table>(10'000'000);

    std::cout << "### Scan for values > " << UINT32_MAX / 2 << " ###\n";
    Scan scan(table);
    scan.scan_gt(UINT32_MAX / 2);

    char c = 110;
    std::cout << "\n### Scan for values containing '" << std::string(1, c) << "' ###\n";
    scan.scan_contains_char(c);
    return 0;
}
