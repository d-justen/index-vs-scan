#include "Table.hpp"
#include "Scan.hpp"

using namespace indexvsscan;

int main(int argc, char *argv[]) {
    auto table = std::make_shared<Table>(10'000'000);
    Scan scan(table);
    scan.scan_gt(UINT32_MAX / 2);
    return 0;
}
