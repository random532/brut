CC?=cc
CFLAGS+= -rdynamic -fcommon -I${LOCALBASE}/include/glib-2.0/ -I${LOCALBASE}/lib/glib-2.0/include -I${LOCALBASE}/include/gdk-pixbuf-2.0/ -I${LOCALBASE}/include/cairo -I${LOCALBASE}/include/pango-1.0 -I${LOCALBASE}/include/gtk-3.0 -I${LOCALBASE}/include/atk-1.0 -I${LOCALBASE}/include/harfbuzz
CFLAGS+= -L${LOCALBASE}/lib/ -lgdk-3  -lgio-2.0 -lgtk-3 -lgobject-2.0 -lglib-2.0


SOURCES= *.c wireless/*.c disks/*.c

all: brut

brut: $(SOURCES)
	$(CC) -o brut $(SOURCES) -DPATH='"${LOCALBASE}"' $(CFLAGS)
