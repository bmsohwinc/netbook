## Points
- Metcalfe's Law
	- The value of a network is proportional to square of number of users
		- For `N` users, a network can have max of `N * (N - 1)` connections, hence the law

- P2P has no central server. Every node is a client/server
	- Email is inherently P2P

- RFID is battery-less, can communicate in a radius of few meters
- Sensor networks - constantly relay data to other nodes

- computer networks can be categorized into: 
	- **transmission technology**
	- **scale**

- transmission technology
	- Unicast
	- Multicast
	- Broadcast

- scale level
	- PAN - bluetooth
	- LAN - Wireless hotspots
		- WiFi is IEEE 802.11
	- MAN - Cable TV networks

- Subnet = Router (or Switch) + Transmission lines
	- integral to WAN

- **Routing** and **Forwarding** algorithms help transmit packets from one router to another

- connecting LAN and WAN creates internetwork
	- connect via **Gateway**

### Network software
- protocol hierarchies
	- each layer is like a VM
	- each layer hides how it and lower layers work when communicating with higher layers and vice versa

- protocols are predetermined between Layer-N peers

- problems and solutions in layered network structure
	- message is very huge -> chunk it into packets
	- packets don't arrive in order -> use numbering
	- oversubscribed network (congestion) -> use congestion control algorithms
	- one sender is swamping a slow receiver -> apply backpressure and flow control with receiver acks
	- bits in packet is altered/lost -> use error correction codes
	- spoofing -> use encryption
	- limited bandwidth to share -> use statistical multiplexing and dynamically allot transmission bandwidth

- connection-oriented
	- setup a connection negotiation to exchange 
	- byte stream for real-time or continuous data
	- message sequence for discrete data

- connection-less
	- similar to fire and forget (unreliable datagram)
	- could have acks and replies (db calls)

- example service calls in connection-oriented network
	- LISTEN - server listens for connections
	- CONNECT - client sends connection request
	- ACCEPT - server accepts request
	- RECEIVE - server waits for messages
	- SEND - client sends messages
	- DISCONNECT - client requests end of connection

- example service calls in connection-less network
	- RECEIVE - server waits for messages
	- SEND - client sends messages

- service v/s protocols
	- service is b/w layer n and layer n + 1
		- abstract view of what to do
	- protocol is b/w peer layers
		- the how to do of the service

- OSI model
	- Physical
		- sends bits, ensures the same bit is received at other side
	- Data link
		- sends frames - groups of thousands of bytes
	- Network
		- routing frames/packets
		- handling congestion and heterogenous networks/protocols
	- Transport
		- fragment packets, provide end-to-end channel for transmission
		- directly interacts with src and dest
			- L1, L2, L3 only interact with neighboring layers
	- Session
		- track current transmiteer, prevent race conditions
	- Presentation
		- allows common data structure to be used for communication
	- Application
		- user protocols like HTTP, FTP, SMTP

- TCP/IP model
	- Link
		- this layer is connectionless
		- interface b/w trx lines and packets/hosts
	- Internet
		- heart of the architecture
		- allows hosts to send/receive packets independently
		- doesn't worry about ordering
	- Transport
		- splits packets into messages, orders them
		- can implement flow control to handle traffic
		- UDP is used for prompt delivery than an accurate delivery
	- Application
		- HTTP, DNS, RTP, etc. 



till pg 85
