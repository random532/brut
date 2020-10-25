
------------------------
xdisk
------------------------
![](screenshot/xdisk1.png)

-----------------------
FAQ
-----------------------

1. What is xdisk?<br>
xdisk is a partition editor for FreeBSD with a graphical user interface.<br><br>

2. How does it look?<br>
![](screenshot/scrot_1.png)
![](screenshot/scrot_2.png)
![](screenshot/scrot_3.png)
![](screenshot/scrot_4.png)

2. What can I do with it?<br>
You can..<br>
   - inspect hard disks, memory cards, sd cards<br>
   - create/destroy partitioning schemes<br>
   - add/remove/modify partitions<br>
   - mount/unmount<br>
   - create file systems<br><br>

3. What are the dependencies?<br>
gtk3 and sudo. "pkg install gtk3" is recommended.<br><br>

4. Is it safe? <br>
Start xdisk as regular user. For root commands, it has sudo(8) backend.<br>
Password is piped to sudo via named pipe. You can change <br>
sudo behavior by editing its configuration file /usr/local/etc/sudoers.<br><br>

5. How do I install xdisk?<br>
Install it as a port:<br>
- Download ports/Makefile and ports/pkg-descr<br>
- Run "make makesum" and "make install clean"<br>
- (recommended: Run "dbus-uuidgen --ensure", for dbus)<br>
- Start it with xdisk :)<br><br>

Or build as a standalone binary:<br>
1. Download the source files (without the /ports folder). I will add a tarball in the future.
2. Make sure you have gtk3 and sudo installed.<br>
3. Run "make LOCALBASE=/usr/local"<br>
4. Start the binary (./xdisk).<br><br>

6. How to uninstall?<br>
run "pkg remove xdisk"<br><br>
