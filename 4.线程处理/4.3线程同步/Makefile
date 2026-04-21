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


rwlock_write_hungry:rwlock_write_hungry.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

rwlock_hungry_solved:rwlock_hungry_solved.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

condition_var:condition_var.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@