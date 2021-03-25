
------------------------
brut
------------------------

-----------------------
FAQ
-----------------------

1. What is brut?<br>
A standalone GUI (graphical user interface) for admin tasks in FreeBSD.<br><br>
2. Screenshots:<br><br>

Main view - control panel:<br>
![](screenshot/scrot20.png)
<br>Partition Editor - Overview of disks:<br>
![](screenshot/scrot21.png)
<br>Partition Editor - edit stuff with simple mouseclicks:<br>
![](screenshot/scrot18.png)


3. What are the dependencies?<br>
gtk3 and sudo. "pkg install gtk3" is recommended, since that one is large.<br><br>

4. Is it safe? <br>
In general, it translates mouse clicks into shell commands.<br>
Start it as a regular user. For root commands, it has a sudo(8) backend.<br>
The password is piped to sudo via a named pipe (there is no other way). You can change<br>
sudo behavior if you edit its configuration file /usr/local/etc/sudoers.<br>
Currently there are no plans to use polkit.<br><br>

5. How do I install it?<br>
Install it just like any other port:<br>
- Make sure you have /usr/ports directory.<br>
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

