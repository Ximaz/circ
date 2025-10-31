RM	:=	rm -rf

all: circ_client circ_server ./shared/libcirc_shared.a

./shared/libcirc_shared.a:
	$(MAKE) -C shared libcirc_shared.a

circ_client:	./shared/libcirc_shared.a
	$(MAKE) -C client
	cp client/circ_client .

circ_server:	./shared/libcirc_shared.a
	$(MAKE) -C server
	cp server/circ_server .

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean
	$(MAKE) -C shared clean

fclean:
	$(MAKE) -C client fclean
	$(MAKE) -C server fclean
	$(MAKE) -C shared fclean
	@$(RM) circ_client circ_server

re: fclean all
