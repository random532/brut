
CC?=cc
CFLAGS+= -rdynamic -L${LOCALBASE}/lib/ -I${LOCALBASE}/include/ -I${LOCALBASE}/include/glib-2.0/ -I${LOCALBASE}/lib/glib-2.0/include -I${LOCALBASE}/include/cairo -I${LOCALBASE}/include/pango-1.0 -I${LOCALBASE}/include/gdk-pixbuf-2.0/ -I${LOCALBASE}/include/atk-1.0 -I${LOCALBASE}/include/gtk-3.0 -lgtk-3 -lgobject-2.0

SOURCES= mainwindow.c treeview.c lang.c subr.c menubar.c editorWindow.c gridEntries.c on_combos_changed.c edit_clicked.c

all: xdisk

xdisk: $(SOURCES)
	$(CC) -o xdisk $(SOURCES) $(CFLAGS)

