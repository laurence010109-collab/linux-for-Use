CC:=gcc

fork_fd_test:fork_fd_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@


erlou:erlou.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

execve_test:execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

fork_execve_test:fork_execve_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

waitpid_test:waitpid_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

unnamed_pipe_test:unnamed_pipe_test.c
	-$(CC) -o $@ $^
	-./$@ "hello world"
	-rm ./$@

fifo_write:fifo_write.c
	-$(CC) -o $@ $^

fifo_read:fifo_read.c
	-$(CC) -o $@ $^

shared_memory:shared_memory.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

shared_memory_block:shared_memory_block.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

father_son_mq_test:father_son_mq_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@