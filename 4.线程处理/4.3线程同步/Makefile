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


unnamed_sem_bin_thread_condition:unnamed_sem_bin_thread_condition.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


unnamed_sem_bin_thread:unnamed_sem_bin_thread.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


unnamed_sem_bin_process_condition:unnamed_sem_bin_process_condition.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

unnamed_sem_bin_process:unnamed_sem_bin_process.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

unnamed_sem_bin_process_isolate:unnamed_sem_bin_process_isolate.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


unnamed_sem_count_thread:unnamed_sem_count_thread.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


unnamed_sem_count_process:unnamed_sem_count_process.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@

named_sem_bin:named_sem_bin.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@


thread_pool_test:thread_pool_test.c
	-$(CC) -o $@ $^ -lpthread
	-./$@
	-rm ./$@