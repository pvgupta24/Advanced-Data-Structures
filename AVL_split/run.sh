g++ test_gen.cpp
./a.out > $1
g++ avl_split.cpp
./a.out < $1