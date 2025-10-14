RM	:=	rm -rf

all: circ_client circ_server

circ_client:
	$(MAKE) -C client
	cp client/circ_client .

circ_server:
	$(MAKE) -C server
	cp server/circ_server .

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean

fclean:
	$(MAKE) -C client fclean
	$(MAKE) -C server fclean
	@$(RM) circ_client circ_server

re: fclean all
