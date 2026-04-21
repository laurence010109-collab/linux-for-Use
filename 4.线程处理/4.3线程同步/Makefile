CC:=gcc

race_condition_test:race_condition_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

mutex_test:mutex_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


rwlock_test_writer_unlock:rwlock_test_writer_unlock.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

rwlock_test:rwlock_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

rwlock_rw_alternate:rwlock_rw_alternate.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@