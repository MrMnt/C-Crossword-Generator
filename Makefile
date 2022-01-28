build:
	cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -S . -B build

debug:
	cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S . -B debug

clean:
	rm -rf ./build ./debug

rebuild: clean build