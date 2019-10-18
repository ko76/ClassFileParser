classDumpFile: classDumpFile.cpp
	g++-9 -o classDumpFile classDumpFile.cpp classStream.hpp classStream.cpp

clean:
	rm -f classDumpFile *.o
