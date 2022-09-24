CC=gcc

make: main.c
	$(CC) main.c -o iCode

run: main.c
	$(CC) main.c -o iCode
	./iCode test.il

clean:
	rm iCode
