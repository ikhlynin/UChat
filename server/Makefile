all: uchat_server libmx

libmx:
	@make -C ../libs/libmx

uchat_server: obj
	@clang -std=c11 -I inc obj/*.o ../libs/libmx/libmx.a -o uchat_server -lpthread -lsqlite3
	@mv uchat_server ../

obj: src/*.c inc/*.h
	@mkdir -p obj
	@clang -std=c11 -I inc -c src/*.c
	@mv *.o obj

uninstall:
	@rm -f ../uchat_server
	@rm -rf obj

client: clobj
	@clang -std=c11 -Wall -Werror -I inc *.o ../libs/libmx/libmx.a -o dummy_client -lpthread
	@rm -rf *.o

clobj:
	@clang -std=c11 -Wall -Werror -I inc -I ../libs/libmx/inc -c src/client/*.c

reinstall: uninstall all


