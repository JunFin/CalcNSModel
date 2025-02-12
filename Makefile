clean:
	rm -f *.o main library.so
	cd Classes && rm -f *.o 
	cd Tests && rm -f *.o 
main *.h, *.cpp Classes/*.cpp, Classes/*.h:
	g++ -std=c++17 -fsanitize=address -Wall -Wextra -g -O0 -shared -fPIC Classes/cell.cpp Classes/waterCell.cpp Classes/wallCell.cpp Classes/staticWallCell.cpp Classes/movingWallCell.cpp Classes/field.cpp  -o library.so -arch arm64 -arch x86_64