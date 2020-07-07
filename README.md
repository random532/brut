------------------------
xdisk
------------------------

Q: What is xdisk?<br>
A: xdisk is a partition editor for FreeBSD with a graphical user interface.<br>

Q: What can I do with it?<br>
A: You can..<br>
   - inspect hard disks, memory cards, sd cards<br>
   - create/destroy partitioning schemes<br>
   - add/remove/modify partitions<br>
   - mount/unmount<br>
   - create file systems<br>
   
Q: What are the dependencies?<br>
A: It uses gtk3. "pkg install gtk3" is recommended.<br>
   Other than that, it only uses system tools (e.g. geom, gpart, newfs).<br>

Q: How do you install xdisk?<br>
A: Install as a port:<br>
1. Download ports/Makefile and ports/pkg-descr
2. Run "make makesum" and "make install clean"
3. (recommended: Run "dbus-uuidgen --ensure", for dbus)
4. Start it with xdisk :)<br>

Q: How to uninstall?<br>
A: run "pkg remove xdisk"<br>

Q: Is it safe? <br>
A: Non-root users can see the partitions, only root can edit them. <br>

Q: Why is this not an official port?<br>
A: It needs more testing. <br>
   I only tested it on a thinkpad x220 and a raspberry pi 3.

![](screenshot/xdisk1.png)
![](screenshot/xdisk-2.png)
![](screenshot/xdisk-3.png)
![](screenshot/xdisk-4.png)
