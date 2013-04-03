all:
	g++ -o test *.cpp -lcurl
clean:
	rm -f test
