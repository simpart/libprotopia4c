# Protopia4c
This is common C library for packet analyzing or generating.<br>
This library makes it easier to develop packet processing.

## Functions
This list is functions of protopia.<br>
The following functions are implemented for each supported protocol.

| function   | Description |
|:-----------|:------------|
| dump       | defined functions for display protocol header of a packet contents to standerd I/O. |
| Header     | defined functions for changing header contents or getting header contents. |
| Classifier | defined functions for check header contents whether it is same value parameter. |

## Supported protocol
- Ethernet
- IP
- ARP
- ICMP
- (TCP)
- (UDP)
- (DHCP)

## Quick start
```
cd /path/to/protopia
sudo make           # then created shared library object at ./bin
sudo make install   # then copy a library object (libprotopia.so) to /usr/lib 
# please see the /path/to/protopia/sample
```
