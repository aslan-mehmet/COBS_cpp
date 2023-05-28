all: encodeTest decodeTest bothTest

bothTest:
	mkdir -p build
	g++ -I.. ../cobs.cpp test_cobs_both.cpp -lgtest -lpthread -o build/bothTest
	build/bothTest

encodeTest:
	mkdir -p build
	g++ -I.. ../cobs.cpp test_cobs_encode.cpp -lgtest -lpthread -o build/encodeTest
	build/encodeTest

decodeTest:
	mkdir -p build
	g++ -I.. ../cobs.cpp test_cobs_decode.cpp -lgtest -lpthread -o build/decodeTest
	./build/decodeTest