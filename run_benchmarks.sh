# Build
cd cmake-build-release
make -j2

# Int Single-Threaded
./src/Main 100000 int st 1000 1000 leq
mv out.csv ../visualization/int_100k_single_1k_distinct.csv
./src/Main 100000 int st 1000 50000 leq
mv out.csv ../visualization/int_100k_single_50k_distinct.csv
./src/Main 1000000 int st 1000 1000 leq
mv out.csv ../visualization/int_1m_single_1k_distinct.csv
./src/Main 1000000 int st 1000 500000 leq
mv out.csv ../visualization/int_1m_single_500k_distinct.csv
./src/Main 10000000 int st 1000 1000 leq
mv out.csv ../visualization/int_10m_single_1k_distinct.csv
./src/Main 10000000 int st 1000 1000000 leq
mv out.csv ../visualization/int_10m_single_1m_distinct.csv
./src/Main 10000000 int st 1000 5000000 leq
mv out.csv ../visualization/int_10m_single_5m_distinct.csv

# Int Multi-Threaded
numactl -N2 -m2 ./src/Main 100000 int mt 1000 1000 leq
mv out.csv ../visualization/int_100k_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 int mt 1000 50000 leq
mv out.csv ../visualization/int_100k_multi_50k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int mt 1000 1000 leq
mv out.csv ../visualization/int_1m_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int mt 1000 500000 leq
mv out.csv ../visualization/int_1m_multi_500k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int mt 1000 1000 leq
mv out.csv ../visualization/int_10m_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int mt 1000 1000000 leq
mv out.csv ../visualization/int_10m_multi_1m_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int mt 1000 5000000 leq
mv out.csv ../visualization/int_10m_multi_5m_distinct.csv

# String Single-Threaded
./src/Main 100000 string st 1000 1000 leq
mv out.csv ../visualization/int_100k_single_1k_distinct.csv
./src/Main 100000 string st 1000 50000 leq
mv out.csv ../visualization/int_100k_single_50k_distinct.csv
./src/Main 1000000 string st 1000 1000 leq
mv out.csv ../visualization/int_1m_single_1k_distinct.csv
./src/Main 1000000 string st 1000 500000 leq
mv out.csv ../visualization/int_1m_single_500k_distinct.csv
./src/Main 10000000 string st 1000 1000 leq
mv out.csv ../visualization/int_10m_single_1k_distinct.csv
./src/Main 10000000 string st 1000 1000000 leq
mv out.csv ../visualization/int_10m_single_1m_distinct.csv
./src/Main 10000000 string st 1000 5000000 leq
mv out.csv ../visualization/int_10m_single_5m_distinct.csv

# String Multi-Threaded
numactl -N2 -m2 ./src/Main 100000 string mt 1000 1000 leq
mv out.csv ../visualization/string_100k_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 string mt 1000 50000 leq
mv out.csv ../visualization/string_100k_multi_50k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string mt 1000 1000 leq
mv out.csv ../visualization/string_1m_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string mt 1000 500000 leq
mv out.csv ../visualization/string_1m_multi_500k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string mt 1000 1000 leq
mv out.csv ../visualization/string_10m_multi_1k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string mt 1000 1000000 leq
mv out.csv ../visualization/string_10m_multi_1m_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string mt 1000 5000000 leq
mv out.csv ../visualization/string_10m_multi_5m_distinct.csv