g++ -std=c++17 -DABS -O2 -Wall -Wextra -Wshadow $1.cpp -o $1 && ./$1
cpp hash.cpp -dD -P -fpreprocessed | tr -d "[:space:]" | md5sum | cut -c -6