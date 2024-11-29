clean:
	rm -f *.o test
test *.cpp, *.h:
	g++ -std=c++11 -fsanitize=address -Wall -Wextra -g -O0 ../Classes/cell.cpp ../Classes/waterCell.cpp ../Classes/wallCell.cpp ../Classes/staticWallCell.cpp ../Classes/movingWallCell.cpp ../Classes/field.cpp test_waterCell.cpp test_staticWallCell.cpp test_movingWallCell.cpp test_field.cpp test.cpp -o test
