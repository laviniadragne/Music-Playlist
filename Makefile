build: tema1

tema1: tema1.c
	gcc tema1.c -o tema1 -Wall -Wextra

clean:
	rm -f tema1


