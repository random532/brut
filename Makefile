CC?=cc
CFLAGS+= -rdynamic -I${LOCALBASE}/include/glib-2.0/ -I${LOCALBASE}/lib/glib-2.0/include -I${LOCALBASE}/include/gdk-pixbuf-2.0/ -I${LOCALBASE}/include/cairo -I${LOCALBASE}/include/pango-1.0 -I${LOCALBASE}/include/atk-1.0 -I${LOCALBASE}/include/gtk-3.0
CFLAGS+= -L${LOCALBASE}/lib/ -lgdk-3  -lgio-2.0 -lgtk-3 -lgobject-2.0

SOURCES= mainWindow.c treeviews.c lang.c subroutines.c menubar.c editorWindow.c editorGridEntries.c on_combos_changed.c applyButtonClicked.c mount.c root.c about.c groups.c user.c disk.c

all: xdisk

xdisk: $(SOURCES)
	$(CC) -o xdisk $(SOURCES) -DPATH='"${LOCALBASE}"' $(CFLAGS)
