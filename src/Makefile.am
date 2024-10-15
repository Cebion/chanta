SUBDIRS = ima data

CXXFLAGS = -Wall -g
LIBS = -lSDL -lSDL_image -lSDL_mixer
DEFS = -DDATADIR=\"${data_dir}\" -DLOCALEDIR=\"${localedir}\" -DVERSION=\"${version}\"

bin_PROGRAMS = chanta

chanta_SOURCES = main.cpp Mundo.cpp Imagen.cpp Protagonista.cpp Escena.cpp \
Juego.cpp Controles.cpp Animacion.cpp Galeria.cpp Nivel.cpp Procesos.cpp \
Actor.cpp Enemigo.cpp Editor.cpp Cursor.cpp Menu.cpp Simple.cpp Fuente.cpp \
Mundo.h Imagen.h Protagonista.h Escena.h\
Juego.h Controles.h Animacion.h Galeria.h Nivel.h Procesos.h Actor.h \
Enemigo.h Editor.h Cursor.h Menu.h Simple.h Fuente.h Cadena.h Cadena.cpp\
Item.h Item.cpp Camara.cpp Camara.h util.h util.cpp

EXTRA_DIST = Makefile.mingw Doxyfile 
