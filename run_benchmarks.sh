cd cmake-build-release
make -j2
./src/Main 1000000 0 0 100 1000000
mv out.csv ../visualization/int_1m_single_1m_distinct.csv
./src/Main 10000000 0 0 100 1000000
mv out.csv ../visualization/int_10m_single_1m_distinct.csv
./src/Main 10000000 0 0 100 10000000
mv out.csv ../visualization/int_10m_single_10m_distinct.csv
./src/Main 1000000 0 1 100 1000000
mv out.csv ../visualization/int_1m_multi_1m_distict.csv
./src/Main 10000000 0 1 100 1000000
mv out.csv ../visualization/int_10m_multi_1m_distinct.csv
./src/Main 10000000 0 1 100 10000000
mv out.csv ../visualization/int_10m_multi_10m_distinct.csv
./src/Main 1000000 1 0 100 1000000
mv out.csv ../visualization/string_1m_single_1m_distinct.csv
./src/Main 10000000 1 0 100 1000000
mv out.csv ../visualization/string_10m_single_1m_distinct.csv
./src/Main 10000000 1 0 100 10000000
mv out.csv ../visualization/string_10m_single_10m_distinct.csv
./src/Main 1000000 1 1 100 1000000
mv out.csv ../visualization/string_1m_multi_1m_distinct.csv
./src/Main 10000000 1 1 100 1000000
mv out.csv ../visualization/string_10m_multi_1m_distinct.csv
./src/Main 10000000 1 1 100 10000000
mv out.csv ../visualization/string_10m_multi_10m_distinct.csv
