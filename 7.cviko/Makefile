NAME=grafika


CC=g++
#CFLAGS=-std=c99 -Wall -pedantic -W -g
CFLAGS=-o -Wextra -I. -I/usr/local/include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs


#all: $(NAME)


# $@ je zkratka pro název cíle
# $^ je zkratka pro seznam prerekvizit pravidla
$(NAME): grafika.cpp
	$(CC) $(CFLAGS) $^ -o $@


  