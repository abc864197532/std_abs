g++ -std=c++17 -DABS -Wall -Wextra -Wshadow $1.cpp -o $1 && ./$1
for i in {A..J}; do cp tem.cpp $i.cpp; done;