
------------------------
xdisk
------------------------
![](screenshot/xdisk1.png)

-----------------------
FAQ
-----------------------

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
A: gtk3 and sudo. "pkg install gtk3" is recommended, since it is huge!<br>

Q: How do I install xdisk?<br>
A: Install as a port:<br>
1. Download ports/Makefile and ports/pkg-descr
2. Run "make makesum" and "make install clean"
3. (recommended: Run "dbus-uuidgen --ensure", for dbus)
4. Start it with xdisk :)<br>

Q: How to uninstall?<br>
A: run "pkg remove xdisk"<br>

Q: Is it safe? <br>
A: Start it as regular user. For root commands, it has sudo(8) backend.<br>
Password is piped to sudo via named pipe. You can change your <br>
sudo settings in sudo.conf(5).<br>

Q: How do I mount/unmount?<br>
A: Right-click on a partition. A popup menu will appear.<br>

Q: Why is this not an official port?<br>
A: It needs more testing.<br>
