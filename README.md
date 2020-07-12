
------------------------
xdisk
------------------------
![](screenshot/xdisk1.png)

-----------------------
FAQ
-----------------------

1. Q: What is xdisk?<br>
A: xdisk is a partition editor for FreeBSD with a graphical user interface.<br>

2. Q: What can I do with it?<br>
A: You can..<br>
   - inspect hard disks, memory cards, sd cards<br>
   - create/destroy partitioning schemes<br>
   - add/remove/modify partitions<br>
   - mount/unmount<br>
   - create file systems<br>
   
3. Q: What are the dependencies?<br>
A: gtk3 and sudo. "pkg install gtk3" is recommended.<br>

4. Q: How do I install xdisk?<br>
A: Install as a port:<br>
1. Download ports/Makefile and ports/pkg-descr
2. Run "make makesum" and "make install clean"
3. (recommended: Run "dbus-uuidgen --ensure", for dbus)
4. Start it with xdisk :)<br>

5. Q: How to uninstall?<br>
A: run "pkg remove xdisk"<br>

6. Q: Is it safe? <br>
A: Run xdisk as regular user. For root commands, it has sudo(8) backend.<br>
Password is piped to sudo via named pipe. You can change <br>
sudo behavior in sudo.conf(5).<br>

7. Q: How do I mount/unmount?<br>
A: Right-click on a partition. A popup menu will appear.<br>

8. Q: Why is this not an official port?<br>
A: I want to test it more.<br>
