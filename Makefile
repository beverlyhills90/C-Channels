CC = cc
CFLAGS = -g
AR = ar
ARFLAGS = rcs

SRCS = helpers.c \
       mpsc_pub_ops.c \
       mpsc/channel.c \
       mpsc/cnahnode.c \
       mpsc/recive.c \
       mpsc/send.c
    
OBJS = $(SRCS:.c=.o)

STATIC_LIB = libmpsc.a

.PHONY: all clean fclean

all: $(STATIC_LIB)

$(STATIC_LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^


%.o: %.c helpers.h channels.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(STATIC_LIB) $(SHARED_LIB)
	
fclean:
	rm -f $(OBJS) $(STATIC_LIB) $(SHARED_LIB)
	rm -f $(STATIC_LIB)