all:
	gcc unittests.c -lm -o thing
	./thing
	gcc databasetests.c -lm -o thing
	./thing
	(cd /packer; ./packer bin/octo.h nodes.h octo.h database.h)
