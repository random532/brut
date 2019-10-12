# secret-tool
This is an early version of a GUI partition editor for FreeBSD.
It uses gtk3.

It currently includes:
- partition manager (wrapper around gpart)
- write .img files to disk

As it has a GUI, its use is self-explanatory.


Todo:
- include create file systems (newfs and others)
- make second tab prettier
- turn printfs into debug statements, or remove them
- remove empty lines, meaningless comments..

Bugs:
None 

Wishlist:
-maybe: replace grid view with tree view
