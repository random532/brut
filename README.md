
------------------------
brut
------------------------

-----------------------
FAQ
-----------------------

1. What is brut?<br>
A graphical user interface (GUI) for various admin tasks in FreeBSD.<br><br>
Among its features are:<br>
- disk editor, partition editor<br>
- manage users/groups<br>
- set time and timezone<br>
- very basic wireless settings<br>
- Inspect devices (usb, pci).<br>

2. How does it look?<br>

Screenshots of early versions of brut in wayland/hikari:
![](screenshot/grim8.png)
![](screenshot/grim1.png)
![](screenshot/grim4.png)


3. What are the dependencies?<br>
gtk3 and sudo. "pkg install gtk3" is recommended, since that one is large.<br><br>

4. Is it safe? <br>
In general, it translates mouse clicks into shell commands.<br>
Start it as a regular user. For root commands, it has a sudo(8) backend.<br>
The password is piped to sudo via a named pipe (there is no other way). You can change<br>
sudo behavior by editing its configuration file /usr/local/etc/sudoers.<br>
Currently there are no plans to use polkit.<br><br>

5. How do I install it?<br>
Install it just like any other port:<br>
- Download ports/Makefile and ports/pkg-descr<br>
- Run "make makesum" and "make install clean"<br>
- (recommended: Run "dbus-uuidgen --ensure", for dbus)<br>
- The start command is: brut :)<br><br>

Or build as a standalone binary:<br>
1. Download the source files (no need for the /ports, /screenshots, /binary folder).
2. Make sure you have gtk3 and sudo installed.<br>
3. Run "make LOCALBASE=/usr/local"<br>
4. Start the binary (./brut).<br><br>

Or download the binary located under /binary/brut (compiled on 12.1 amd64).<br>
Change permissions, "chmod +x ./brut", then run it.<br><br>

