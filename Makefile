all: install

install:
	@$(MAKE) -C libs/libmx
	@$(MAKE) -C client/
	@$(MAKE) -C server/

uninstall:
	@$(MAKE) -C libs/libmx uninstall
	@$(MAKE) -C client/ uninstall
	@$(MAKE) -C server/ uninstall

reinstall: uninstall install
