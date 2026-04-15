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

