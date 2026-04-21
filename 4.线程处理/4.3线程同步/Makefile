CC:=gcc

race_condition_test:race_condition_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@