CC			:=	gcc
CPPFLAGS	:=	-I ../include/
CFLAGS		:=	-Wall -Wextra -Werror -pedantic -ansi -fPIE 		 \
				-fno-delete-null-pointer-checks -fno-strict-overflow \
				-fno-strict-aliasing -ftrivial-auto-var-init=zero    \
				-Wformat -Wimplicit-fallthrough 					 \
				-U_FORTIFY_SOURCE -D_GLIBCXX_ASSERTIONS 			 \
				-fstack-protector-strong
LIBS		:=	-L../shared/ -lcirc_shared

ifeq ($(PLATFORM),x86_64)
	CFLAGS	+=	-fcf-protection=full -Wl,-z,nodlopen -Wl,-z,noexecstack \
			-Wl,-z,relro -Wl,-z,now -fstack-clash-protection 			\
			-fstrict-flex-arrays=3 -Wtrampolines
endif

ifeq ($(PLATFORM),aarch64)
	CFLAGS	+=	-mbranch-protection=standard
endif

SRCS			:=	$(shell find src -name '*.c')
OBJS			:=	$(SRCS:.c=.o)
NAME			:=	circ_server
SHARED_LIB_PATH	:=	../shared/libcirc_shared.a

VALGRIND_FLAGS	:=	-s							\
					--leak-check=full			\
					--track-origins=yes			\
					--read-var-info=yes			\
					--trace-children=yes		\
					--show-leak-kinds=all		\
					--read-inline-info=yes		\
					--errors-for-leak-kinds=all

RM				:=	rm -rf

all:	$(OBJS)
	$(MAKE) $(NAME)

$(SHARED_LIB_PATH):
	$(MAKE) -C ../shared

$(NAME):	$(SHARED_LIB_PATH) $(OBJS)
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:	fclean all
