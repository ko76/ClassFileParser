classDumpFile: classDumpFile.cpp  
	g++-9 -o classDumpFile classStream.hpp classStream.cpp classDumpFile.cpp

clean:
	rm -f classDumpFile *.o
