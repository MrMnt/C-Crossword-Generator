build:
	cmake -G "MinGW Makefiles" -S . -B build

clean:
	rm -rf ./build

rebuild: clean build