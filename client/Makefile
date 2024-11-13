all: uchat

uchat: obj
	@clang -std=c11 obj/*.o -I inc -o uchat `pkg-config --libs gtk+-3.0` ../libs/libmx/libmx.a -pthread
#	@rm -rf obj
#	mv uchat ../
 
obj: src/*.c inc/*.h
	@mkdir -p obj
	@clang -std=c11 -I inc -c src/*.c `pkg-config --cflags gtk+-3.0`
	@mv *.o obj

uninstall:
	@rm -f ../uchat
	@rm -rf obj

reinstall: uninstall all

