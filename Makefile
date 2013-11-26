all:
	gcc src/wumbo/wumbo.c -lm -o thing
	./thing
	gcc src/octobase/unittests.c -lm -o thing
	./thing
	gcc src/database/databasetests.c -lm -o thing
	./thing
	g++ packer/main.cpp -o packerrun
	./packerrun bin/octo.h src/headers/nodes.h src/headers/octo.h src/headers/database.h
