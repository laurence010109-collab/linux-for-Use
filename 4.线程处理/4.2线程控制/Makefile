CC:=gcc

create_test:create_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-mr ./$@

terminate_test:terminate_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-mr ./$@