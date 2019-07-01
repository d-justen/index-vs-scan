cd cmake-build-release
make -j2
./src/Main 1000000 int st 1000 1000000 leq
mv out.csv ../visualization/int_1m_single_1m_distinct.csv
./src/Main 10000000 int st 1000 1000000 leq
mv out.csv ../visualization/int_10m_single_1m_distinct.csv
./src/Main 10000000 int st 1000 10000000 leq
mv out.csv ../visualization/int_10m_single_10m_distinct.csv
./src/Main 1000000 int mt 1000 1000000 leq
mv out.csv ../visualization/int_1m_multi_1m_distict.csv
./src/Main 10000000 int mt 1000 1000000 leq
mv out.csv ../visualization/int_10m_multi_1m_distinct.csv
./src/Main 10000000 int mt 1000 10000000 leq
mv out.csv ../visualization/int_10m_multi_10m_distinct.csv
./src/Main 1000000 string st 1000 1000000 leq
mv out.csv ../visualization/string_1m_single_1m_distinct.csv
./src/Main 10000000 string st 1000 1000000 leq
mv out.csv ../visualization/string_10m_single_1m_distinct.csv
./src/Main 10000000 string st 1000 10000000 leq
mv out.csv ../visualization/string_10m_single_10m_distinct.csv
./src/Main 1000000 string mt 1000 1000000 leq
mv out.csv ../visualization/string_1m_multi_1m_distinct.csv
./src/Main 10000000 string mt 1000 1000000 leq
mv out.csv ../visualization/string_10m_multi_1m_distinct.csv
./src/Main 10000000 string mt 1000 10000000 leq
mv out.csv ../visualization/string_10m_multi_10m_distinct.csv
