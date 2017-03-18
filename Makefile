asm: class.o cpu.o asm.o
	g++ -o $@ -g $^

%.o: %.cxx
	g++ -c -g -o $@ $^
 
