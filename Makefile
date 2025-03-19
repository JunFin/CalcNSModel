main: *.cpp Classes/*.cpp Classes/*.h
	g++ -std=c++17 -Wall -Wextra -g -O0 -shared -fPIC -o CalcNSModel.so Classes/cell.cpp Classes/waterCell.cpp Classes/wallCell.cpp Classes/staticWallCell.cpp Classes/movingWallCell.cpp Classes/field.cpp exportFunctions.cpp
clean:
	rm -f *.o CalcNSModel.so
	rm -r CalcNSModel.so.dSYM
	cd Classes && rm -f *.o 
	cd Tests && rm -f *.o 