LAMEDIR=../lame-3.89

CFLAGS=-I$(LAMEDIR)/include -O0 -g -Wall

LDFLAGS=-L$(LAMEDIR)/libmp3lame/.libs -g
LIBS=-static -lmp3lame -dynamic -lncurses  -lm

OBJS=lametus.o encoder.o audio_oss.o parser.o

all: lametus

lametus: $(OBJS)
	$(CC) $(LDFLAGS) -o lametus $(OBJS) $(LIBS)

clean:
	rm -f lametus core $(OBJS)
