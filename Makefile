objects := hello.o \
	main.o

main:$(objects)
	gcc -o main $(objects)

main.o:hello.h

hello.o:hello.h

.PHONY: clean

clean:
	rm main $(objects)