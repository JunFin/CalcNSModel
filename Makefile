clean:
	rm -f *.o main
main *.h, *.cpp:
	g++ -v -Wall -Wextra ../Classes/cell.cpp ../Classes/waterCell.cpp ../Classes/wallCell.cpp ../Classes/staticWallCell.cpp ../Classes/movingWallCell.cpp ../Classes/field.cpp main.cpp -o main