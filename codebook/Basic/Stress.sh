g++ main.cpp -o main
g++ gen.cpp -o gen
g++ good.cpp -o good
for i in {1..100} ; do
	./gen > input.txt
	./main < input.txt > output1.txt
	./good < input.txt > output2.txt
	if cmp --silent -- "output1.txt" "output2.txt" ; then
		continue
	fi
	echo Input:
	cat input.txt
	echo Your Output:
	cat output1.txt
	echo Correct Output:
	cat output2.txt
	break
done
echo OK!