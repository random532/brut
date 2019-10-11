
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>


//#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <inttypes.h>


#include <sys/types.h>
#include <sys/sysctl.h>

#define DEBUG	1

#define MAXDSUP 50		/* if you have more disks, increase this */
#define DNAMELEN 10 		/* a disk name string looks like 'ada999 \0'  */

#define GEOMDUMP	"kern.geom.conftxt"
#define BUG			printf("do we rech this?\n");

/* 
* We generally avoid using plural 's' in disks declarations 
* to avoid confusion.
*/



struct disk_info {

char *disk;		/* all disks as one continous string */
size_t disklen;	/* length  */
int numbdisk;	/* number of disks */
char *conftxt;	/* disk setup retrieved via sysctl */
size_t conftxtlen;	/* length */


char dnames[MAXDSUP][DNAMELEN];	/* array of strings, with all disk names */

};

/* avoid /usr/bin/gpart, which is a port */
#define PATHTOGPART "/usr/sbin/" 
		
