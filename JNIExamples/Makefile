test:
	g++-9 -o test -I/usr/include -I/Library/Java/JavaVirtualMachines/jdk-10.0.1.jdk/Contents/Home/include -I/Library/Java/JavaVirtualMachines/jdk-10.0.1.jdk/Contents/Home/include/darwin -Wl,-rpath,/Library/Java/JavaVirtualMachines/jdk-10.0.1.jdk/Contents/Home/lib/server -L/Library/Java/JavaVirtualMachines/jdk-10.0.1.jdk/Contents/Home/lib/server JNIString.cpp -ljvm


clean:
	rm -f test *.o