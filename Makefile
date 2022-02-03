CMAKE_GENERATOR = -G "MinGW Makefiles"


# Release build
rebuild: clean build
build:
	cmake $(CMAKE_GENERATOR) -DCMAKE_BUILD_TYPE=Release -S . -B build
clean_build:
	rm -rf ./build


# Debug build
redebug: clean debug
debug:
	cmake $(CMAKE_GENERATOR) -DCMAKE_BUILD_TYPE=Debug -S . -B debug
clean_debug:
	rm -rf ./debug


clean:
	rm -rf ./build ./debug