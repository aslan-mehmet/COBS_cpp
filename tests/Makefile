all: encodeTest decodeTest bothTest

bothTest: buildFolder
	g++ -I.. ../cobs.cpp test_cobs_both.cpp -lgtest -lpthread -o build/bothTest
	build/bothTest

encodeTest: buildFolder
	g++ -I.. ../cobs.cpp test_cobs_encode.cpp -lgtest -lpthread -o build/encodeTest
	build/encodeTest

decodeTest: buildFolder
	g++ -I.. ../cobs.cpp test_cobs_decode.cpp -lgtest -lpthread -o build/decodeTest
	./build/decodeTest

buildFolder:
	rm -rf build
	mkdir -p build