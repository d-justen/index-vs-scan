# Build
cd cmake-build-release
make -j2

# Int Single-Threaded
numactl -N2 -m2 ./src/Main 100000 int st 0 800 1000 leq
mv out.csv ../visualization/int_100k_single_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 int st 0 800 10000 leq
mv out.csv ../visualization/int_100k_single_10k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 int st 0 800 5000 leq
mv out.csv ../visualization/int_500k_single_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 int st 0 800 50000 leq
mv out.csv ../visualization/int_500k_single_50k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int st 0 800 10000 leq
mv out.csv ../visualization/int_1m_single_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int st 0 800 100000 leq
mv out.csv ../visualization/int_1m_single_100k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 int st 0 800 50000 leq
mv out.csv ../visualization/int_5m_single_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 int st 0 800 500000 leq
mv out.csv ../visualization/int_5m_single_500k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int st 0 800 100000 leq
mv out.csv ../visualization/int_10m_single_100k_distinct.csv

# Int Multi-Threaded
numactl -N2 -m2 ./src/Main 100000 int mt 8 800 1000 leq
mv out.csv ../visualization/int_100k_mt8_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 int mt 16 800 1000 leq
mv out.csv ../visualization/int_100k_mt16_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 int mt 32 800 1000 leq
mv out.csv ../visualization/int_100k_mt32_1k_distinct.csv

numactl -N2 -m2 ./src/Main 500000 int mt 8 800 5000 leq
mv out.csv ../visualization/int_500k_mt8_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 int mt 16 800 5000 leq
mv out.csv ../visualization/int_500k_mt16_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 int mt 32 800 5000 leq
mv out.csv ../visualization/int_500k_mt32_5k_distinct.csv

numactl -N2 -m2 ./src/Main 1000000 int mt 8 800 10000 leq
mv out.csv ../visualization/int_1m_mt8_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int mt 16 800 10000 leq
mv out.csv ../visualization/int_1m_mt16_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 int mt 32 800 10000 leq
mv out.csv ../visualization/int_1m_mt32_10k_distinct.csv

numactl -N2 -m2 ./src/Main 5000000 int mt 8 800 50000 leq
mv out.csv ../visualization/int_5m_mt8_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 int mt 16 800 50000 leq
mv out.csv ../visualization/int_5m_mt16_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 int mt 32 800 50000 leq
mv out.csv ../visualization/int_5m_mt32_50k_distinct.csv

numactl -N2 -m2 ./src/Main 10000000 int mt 8 800 100000 leq
mv out.csv ../visualization/int_10m_mt8_100k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int mt 16 800 100000 leq
mv out.csv ../visualization/int_10m_mt16_100k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 int mt 32 800 100000 leq
mv out.csv ../visualization/int_10m_mt32_100k_distinct.csv

# String Single-Threaded
numactl -N2 -m2 ./src/Main 100000 string st 0 800 1000 leq
mv out.csv ../visualization/string_100k_single_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 string st 0 800 10000 leq
mv out.csv ../visualization/string_100k_single_10k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 string st 0 800 5000 leq
mv out.csv ../visualization/string_500k_single_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 string st 0 800 50000 leq
mv out.csv ../visualization/string_500k_single_50k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string st 0 800 10000 leq
mv out.csv ../visualization/string_1m_single_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string st 0 800 100000 leq
mv out.csv ../visualization/string_1m_single_100k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 string st 0 800 50000 leq
mv out.csv ../visualization/string_5m_single_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 string st 0 800 500000 leq
mv out.csv ../visualization/string_5m_single_500k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string st 0 800 100000 leq
mv out.csv ../visualization/string_10m_single_100k_distinct.csv

# String Multi-Threaded
numactl -N2 -m2 ./src/Main 100000 string mt 8 800 1000 leq
mv out.csv ../visualization/string_100k_mt8_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 string mt 16 800 1000 leq
mv out.csv ../visualization/string_100k_mt16_1k_distinct.csv
numactl -N2 -m2 ./src/Main 100000 string mt 32 800 1000 leq
mv out.csv ../visualization/string_100k_mt32_1k_distinct.csv

numactl -N2 -m2 ./src/Main 500000 string mt 8 800 5000 leq
mv out.csv ../visualization/string_500k_mt8_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 string mt 16 800 5000 leq
mv out.csv ../visualization/string_500k_mt16_5k_distinct.csv
numactl -N2 -m2 ./src/Main 500000 string mt 32 800 5000 leq
mv out.csv ../visualization/string_500k_mt32_5k_distinct.csv

numactl -N2 -m2 ./src/Main 1000000 string mt 8 800 10000 leq
mv out.csv ../visualization/string_1m_mt8_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string mt 16 800 10000 leq
mv out.csv ../visualization/string_1m_mt16_10k_distinct.csv
numactl -N2 -m2 ./src/Main 1000000 string mt 32 800 10000 leq
mv out.csv ../visualization/string_1m_mt32_10k_distinct.csv

numactl -N2 -m2 ./src/Main 5000000 string mt 8 800 50000 leq
mv out.csv ../visualization/string_5m_mt8_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 string mt 16 800 50000 leq
mv out.csv ../visualization/string_5m_mt16_50k_distinct.csv
numactl -N2 -m2 ./src/Main 5000000 string mt 32 800 50000 leq
mv out.csv ../visualization/string_5m_mt32_50k_distinct.csv

numactl -N2 -m2 ./src/Main 10000000 string mt 8 800 100000 leq
mv out.csv ../visualization/string_10m_mt8_100k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string mt 16 800 100000 leq
mv out.csv ../visualization/string_10m_mt16_100k_distinct.csv
numactl -N2 -m2 ./src/Main 10000000 string mt 32 800 100000 leq
mv out.csv ../visualization/string_10m_mt32_100k_distinct.csv