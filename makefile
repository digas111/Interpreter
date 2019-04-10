LIBS = Exec Hash Instr LinkedList Read

libraries:
	rm -rf Libraries/
	mkdir Libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		gcc -c *.c -I../; \
		mv *.o ../Libraries; \
		cd -; \
	done
