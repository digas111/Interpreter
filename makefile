LIBS = Exec Hash Instr LinkedList Read

libraries:
	mkdir Libraries/
	for dir in $(LIBS); do \
		cd $$dir; \
		gcc -c *.c -I../; \
		mv *.o ../../libraries; \
		cd -; \
	done

clean:
	rm -rf Libraries/