g++ test_gen.cpp
./a.out > $1
g++ avl_join.cpp
./a.out < $1