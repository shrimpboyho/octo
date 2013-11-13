all:
	gcc unittests.c -lm -o thing
	./thing
	gcc databasetests.c -lm -o thing
	./thing
	g++ packer/main.cpp -o packerrun
	./packerrun bin/octo.h nodes.h octo.h database.h
