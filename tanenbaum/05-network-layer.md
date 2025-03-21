# Network Layer

- deals with src to dest packet movement, not just immediate next router
- protocol is IP

- Network layer must know the full network structure
- It should choose appropriate path for delivery
- It should not swamp or block lines

## Design issues
- 2 major:
	- How to interface with Transport and Link Layers
	- How to implement internal protocols

- Store and Forward packet switching
	- host sends a packet
	- router receives it
	- but router stores it until it completely receives the packet and performs checksum verification
	- it sends the packet to next router
	- eventually, the packet arrives at the destination machine

- services provided to transport layer
	- they are independent of router technology or network structure
	- ip addressing is consistent in LAN as well as WAN (?)

- IP (Internet protocol) is the basis for entire Internet.
- It is **connection-less**
- Every packet carries the destination IP address
- Every router has routing table based on `<IP : connection line>`
- Depending on traffic, the routing table can dynamically update (routing algorithms)
- ipv4 is `32` bit. ipv6 is `128` bit

- Connection less service uses routing table
- Connection oriented service uses VC table

- VC - Virtual Circuit table
	- in connection-oriented service, first, VC table with id is setup in each router
	- duplicates are handled by adding `{router id + vc id}` as key of table

- Datagram v/s VC networks
	- table size	
	- lookup v/s setup
	- free route v/s vulnerable path
	- bulky packets v/s light references
	

## Routing Algorithms
- routing: deciding where to send
- forwarding: actually moving the packet to the line
- routing algorithms should be: correct, stable (finish in time), fair and efficient (minimize packet travel length and maximize network bandwidth utilization), and robust (continue working even if some node is down)
- best case is to transmit from a node B is along the sink tree rooted at B (min spanning tree)


## Congestion Control Algorithms

## Quality of Service

## Internetworking

## Network Layer in Internet

## 



Till Pg 365


