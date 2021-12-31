all: encodeTest decodeTest

encodeTest:
	mkdir -p build
	g++ -I.. ../cobs.cpp test_COBS_encode.cpp -lgtest -lpthread -o build/encodeTest
	build/encodeTest

decodeTest:
	mkdir -p build
	g++ -I.. ../cobs.cpp test_COBS_decode.cpp -lgtest -lpthread -o build/decodeTest
	./build/decodeTest