if [ $# -ne 2 ] ; then
	g++ -std=c++17 -DABS -Wall -Wextra -Wshadow $1.cpp -o $1
else
	g++ -std=c++17 -DABS -Wall -Wextra -Wshadow $1.cpp -o $1 -fsanitize=address
fi
./$1
chmod +x ./run.sh
./run.sh main [1]