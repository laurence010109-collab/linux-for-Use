CC:=gcc

virtual_memory_test: virtual_memory_test.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

execve_invalid_path: execve_invalid_path.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@

num_endianess_convert: num_endianess_convert.c
	-$(CC) -o $@ $^
	-./$@
	-rm ./$@