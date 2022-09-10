test:practice.o check.o
	@gcc practice.o check.o -lcheck -o test
	@./test
practice.o:
	@gcc -g -c practice.c -I . 
check.o:
	@gcc -g -c tests/check_practice.c -I . -o check.o
clean:
	@rm practice.o test check.o
