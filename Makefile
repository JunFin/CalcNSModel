clean:
	rm -f *.o main library.so
	cd Classes && rm -f *.o 
	cd Tests && rm -f *.o 
main: *.cpp Classes/*.cpp Classes/*.h
	g++ -std=c++17 -Wall -Wextra -g -O0 -shared -fPIC -o library.so Classes/cell.cpp Classes/waterCell.cpp Classes/wallCell.cpp Classes/staticWallCell.cpp Classes/movingWallCell.cpp Classes/field.cpp main.cpp
