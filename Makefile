all:
	gcc unittests.c -lm -o thing
	./thing
	gcc databasetests.c -lm -o thing
	./thing
