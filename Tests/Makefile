clean:
	rm -f *.o test
test *.cpp, *.h:
	g++ -Wall -Wextra ../Classes/cell.cpp ../Classes/waterCell.cpp ../Classes/wallCell.cpp ../Classes/staticWallCell.cpp ../Classes/movingWallCell.cpp ../Classes/field.cpp test_waterCell.cpp test_staticWallCell.cpp test_movingWallCell.cpp test_field.cpp test.cpp -o test
	./test