all: encodeTest decodeTest

encodeTest:
	g++ -I.. ../cobs.cpp test_COBS_encode.cpp -lgtest -lpthread -o build/encodeTest
	build/encodeTest

decodeTest:
	g++ -I.. ../cobs.cpp test_COBS_decode.cpp -lgtest -lpthread -o build/decodeTest
	./build/decodeTest