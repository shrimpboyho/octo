all:
	gcc unittests.c -lm -o thing
	./thing
	gcc databasetests.c -lm -o thing
	./thing
	g++ packer/main.cpp -o packer
	./packer bin/octo.h nodes.h octo.h database.h
