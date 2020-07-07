------------------------
xdisk
------------------------

Q: What is xdisk?<br>
A: xdisk is a partition editor for FreeBSD with a graphical user interface.<br>

Q: What can I do with it?<br>
A: - view all hard disks, memory cards, sd cards on the system<br>
   - create/destroy partitioning schemes<br>
   - add/remove/modify partitions<br>
   - mount/unmount<br>
   - create file systems<br>
   
Q: What are the dependencies?<br>
A: It uses gtk3. "pkg install gtk3" is recommended. Other than that, it only uses
system tools (e.g. geom, gpart, newfs).<br>

Q: How do you install xdisk?<br>
A: Install as a port:<br>
1. Download ports/Makefile and ports/pkg-descr
2. Run "make makesum" and "make install clean"
3. (recommended: Run "dbus-uuidgen --ensure", for dbus)
4. Start it with xdisk :)<br>

Q: How to uninstall?<br>
A: run "pkg remove xdisk"<br>

Q: Is it safe? <br>
A: Yes. It carefully translates mouse clicks into gpart commands.<br>

Q: Why is this not an official port yet?<br>
A: It needs more testing.

![](screenshot/xdisk-1.png)
![](screenshot/xdisk-2.png)
![](screenshot/xdisk-3.png)
![](screenshot/xdisk-4.png)
