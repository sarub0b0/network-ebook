CC = clang++

ifndef $(COMPILE_TYPE)
	COMPILE_TYPE=debug
	#COMPILE_TYPE=profile
	#COMPILE_TYPE=release
endif

# MESSAGE_FLAGS = -DMESSAGE_WARNING

FLAGS = ${MESSAGE_FLAGS}
GENERAL_FLAGS = -Wall ${FLAGS}

INCS = -I../include
LIBS = -L../lib -lapp `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

ifeq ($(COMPILE_TYPE), debug)
	GCC_FLAGS = -g ${GENERAL_FLAGS}
endif
ifeq ($(COMPILE_TYPE), profile)
	GCC_FLAGS = -pg ${GENERAL_FLAGS}
endif
ifeq ($(COMPILE_TYPE), release)
	GCC_FLAGS = ${GENERAL_FLAGS}
endif

SUB_OBJECTS = graphics.o
OBJECTS = app.o ${SUB_OBJECTS}

all: libapp.a app

libapp.a: ${OBJECTS}
	ar rc ../lib/libapp.a ${OBJECTS} && ranlib ../lib/libapp.a

app: app.o
	$(CC) $(GCC_FLAGS) app.o -o app ${INC} ${LIBS}

app.o: app.cpp
	$(CC) $(GCC_FLAGS) app.cpp -c ${INCS}

graphics.o: graphics.cpp
	$(CC) $(GCC_FLAGS) graphics.cpp -c ${INCS}

clean:
	rm -f ../lib/libapp.a *.o app
