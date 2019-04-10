LIBS = Exec Hash Instr LinkedList Read

libraries:
	mkdir Libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		gcc -Wall -c *.c -I../; \
		mv *.o ../Libraries; \
		cd -; \
	done
	gcc -Wall Main/main.c -o main
clean:
	rm -rf Libraries/