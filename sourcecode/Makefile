
CC=cc
CFLAGS= -g -Wall -lX11 -rdynamic -lXm -lXt -L/usr/local/lib/ -I/usr/local/include/ -I/usr/local/include/gtk-3.0 -L/usr/local/lib -I /usr/local/include -I/usr/local/include/glib-2.0/ -I/usr/local/lib/glib-2.0/include -I/usr/local/include/pango-1.0/ -I/usr/local/include/cairo -I/usr/local/include/gdk-pixbuf-2.0/ -I/usr/local/include/atk-1.0 -lgtk-3 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lgdk_pixbuf-2.0 -lpangocairo-1.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0

LDFLAGS= -L/usr/local/lib/ 

SOURCES= mainwindow.c treeview.c lang.c subr.c menubar.c editorWindow.c gridEntries.c on_combos_changed.c edit_clicked.c

all: xdisk

xdisk: $(SOURCES)
	$(CC) -o xdisk $(SOURCES) $(CFLAGS)

