echo "WARNING: remove the bigger values if you dont have 4gb of ram"
sleep 5
echo "-------------------------- NON-OPTIMIZED TESTS -----------------------------  "
for OPT in 10 100 1000 10000 100000 1000000 10000000 100000000 200000000
do
	echo N = $OPT
	g++ -std=c++11 -Wall -DMAXIMUM=$OPT speed_test_vector.cpp -o vector
	g++ -std=c++11 -Wall -DMAXIMUM=$OPT speed_test_devector.cpp -o devector
	echo "STL VECTOR WITH PUSH_BACK:"
	time ./vector
	echo "XTRM0 VECTOR WITH MIXED PUSH_BACK AND PUSH_FRONT:"
	time ./devector
done

echo "---------------------------- OPTIMIZED TESTS -------------------------------  "
for OPT in 10 100 1000 10000 100000 1000000 10000000 100000000 200000000
do
	echo N = $OPT
	g++ -std=c++11 -O3 -Wall -DMAXIMUM=$OPT speed_test_vector.cpp -o vector
	g++ -std=c++11 -O3 -Wall -DMAXIMUM=$OPT speed_test_devector.cpp -o devector
	echo "STL VECTOR WITH PUSH_BACK:"
	time ./vector
	echo "XTRM0 VECTOR WITH MIXED PUSH_BACK AND PUSH_FRONT:"
	time ./devector
done

echo "------------------------- CRAZY OPTIMIZED TESTS -----------------------------  "
for OPT in 10 100 1000 10000 100000 1000000 10000000 100000000 200000000
do
	echo N = $OPT
	g++ -std=c++11 -O3 -march=native -flto -fwhole-program -Wall -DMAXIMUM=$OPT speed_test_vector.cpp -o vector
	g++ -std=c++11 -O3 -march=native -flto -fwhole-program -Wall -DMAXIMUM=$OPT speed_test_devector.cpp -o devector
	echo "STL VECTOR WITH PUSH_BACK:"
	time ./vector
	echo "XTRM0 VECTOR WITH MIXED PUSH_BACK AND PUSH_FRONT:"
	time ./devector
done
