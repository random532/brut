
------------------------
xdisk
------------------------
![](screenshot/xdisk1.png)

-----------------------
FAQ
-----------------------

1. What is xdisk?<br>
xdisk is a partition editor for FreeBSD with a graphical user interface.<br>

2. What can I do with it?<br>
You can..<br>
   - inspect hard disks, memory cards, sd cards<br>
   - create/destroy partitioning schemes<br>
   - add/remove/modify partitions<br>
   - mount/unmount<br>
   - create file systems<br>
   
3. What are the dependencies?<br>
gtk3 and sudo. "pkg install gtk3" is recommended.<br>

4. How do I install xdisk?<br>
Install as a port:<br>
1. Download ports/Makefile and ports/pkg-descr
2. Run "make makesum" and "make install clean"
3. (recommended: Run "dbus-uuidgen --ensure", for dbus)
4. Start it with xdisk :)<br>

5. How to uninstall?<br>
run "pkg remove xdisk"<br>

6. Is it safe? <br>
Start xdisk as regular user. For root commands, it has sudo(8) backend.<br>
Password is piped to sudo via named pipe. You can change <br>
sudo behavior in sudo.conf(5).<br>

7. How do I mount/unmount?<br>
Right-click on a partition. A popup menu will appear.<br>

8. Why is this not an official port?<br>
I want to test it more.<br>
