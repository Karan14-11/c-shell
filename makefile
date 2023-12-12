
CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = shell

SRCS = main.c backgrnd_fn.c complete.c datastructures.c def_term.c dir_rec.c dir_work.c directory.c execute.c fil_rec.c fil_work.c lines_written.c no_ascee.c paste.c peek_flag.c peek.c proclore.c  purge.c read_lines.c seek_flag.c seek.c   token.c warp_run.c warp_tok.c warp.c write_com.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)