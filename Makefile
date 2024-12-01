clean:
	rm -f *.o main
main *.h, *.cpp Classes/*.cpp, Classes/*.h:
	g++ -std=c++17 -fsanitize=address -Wall -Wextra -g -O0 Classes/cell.cpp Classes/waterCell.cpp Classes/wallCell.cpp Classes/staticWallCell.cpp Classes/movingWallCell.cpp Classes/field.cpp main.cpp -o main