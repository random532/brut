
CC?=cc
CFLAGS+= -rdynamic -L/usr/local/lib/ -I/usr/local/include/ -I/usr/local/include/glib-2.0/ -I/usr/local/lib/glib-2.0/include -I/usr/local/include/cairo -I/usr/local/include/pango-1.0 -I/usr/local/include/gdk-pixbuf-2.0/ -I/usr/local/include/atk-1.0 -I/usr/local/include/gtk-3.0 -I /usr/local/include  -lgtk-3 -lgobject-2.0


SOURCES= mainwindow.c treeview.c lang.c subr.c menubar.c editorWindow.c gridEntries.c on_combos_changed.c edit_clicked.c

all: xdisk

xdisk: $(SOURCES)
	$(CC) -o xdisk $(SOURCES) $(CFLAGS)

