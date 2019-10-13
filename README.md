

# partition editor
This is an early version of a GUI partition editor for FreeBSD.

It runs in a window manager of your choice (gnome, lxde, ...).
It uses gtk3, so you need pkg install gtk3.


1.It currently includes:

- view disks, partitions, slices, disk labels, and device names
- create/destroy disks or slices, add, remove, modify, resize partitions
- set labels or attributes
- write .img files to disk (with optional sha checksum checking)
- add file systems (ufs, ntfs)

As it has a GUI, its use is self-explanatory.


2. Todo:
- improve creating file systems
- remove printfs, error checking

3. Bugs:
Please report them

4. Wishlist:
-maybe: replace grid view with a tree view

5. How to use this:
- Download the files into a folder
- cd into that folder
- type "make"
- type "./my" 
- enjoy the GUI :-)

6. Screenshot
![](screenshot/20191013_150244_compress41_crop_62.jpg)
