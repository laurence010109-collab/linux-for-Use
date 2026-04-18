CC:=gcc

create_test:create_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-mr ./$@