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
	- lookup table v/s setup conxn
	- free route v/s vulnerable path
	- bulky packets v/s light references
	

## Routing Algorithms
- routing: deciding where to send
- forwarding: actually moving the packet to the line
- routing algorithms should be: correct, stable (finish in time), fair and efficient (minimize packet travel length and maximize network bandwidth utilization), and robust (continue working even if some node is down)
- best case is to transmit from a node B is along the sink tree rooted at B (min spanning tree)

- non-adaptive are static. won't change. example: router to laptop at home
- adaptive: change routing rules based on metrics (hops, traffic, health)

- Edge weight is a weighted average of:
	- physical distance in kms
	- number of hops
	- bandwidth
	- average packet transfer delay
- Dijkstra is used for shortest path computation

- Flooding is one way which guarantees shortes path, is robust, but have
	- packets duplicated
	- infinite retransmissions
- it can be avoided by setting a counter `k`  on each packet that represents network diameter
- another way is to maintain seen packet numbers at each routers limited to k

- distance vector routing helps routers estimate distance to all routers by sharing the relative distances with their neighbors
	- but this is susceptible to **Count to Infinity** problem
		- if a node receives a data from a neighbor who based it on the same node but that node doesn't know that the data was based on itself

- link state routing also uses **flooding**, but uses _sequence number_ and _age_ fields to prevent count to infinity
	- this is the popular and deployed algorithm

- hierarchical routing helps reduce routing table size for faster routing
	- zones, regions, clusters allow effective grouping
	- but increases number of hops for communication

- **broadcast**ing effectively requires spanning tree derivation
	- packet coming from spanning tree edge is flooded
	- coming from any other edge/link is discarded

- multicast can be done by creating virtual groups that request data
	- a spanning tree with a core node optimizes multicast
	- needs more reading about deciding the core (it's usually the sender) and protocols (DVMRP, MOSPF)

- anycast is used in DNS. no specific node is needed -- any node can provide the data if they have it

- Mobile routing requires every host to have a **home** address.
	- Mobile hosts keep acquiring new addresses, but home address is invariable. This is a **home agent**
	- Senders send to home address, which forwards to mobile host. This is called **tunneling**
	- Security is important, and needs more study

- ad hoc networks routing
	- varying topology means routing table generated on-demand
	- nodes withing coverage circle form connections
	- sender sends ROUTE_RQUEST packet to destination. destination sends ROUTE_REPLY packet
	- packets include seq num and age/ttl to prevent count to infinity
	- routes are updated periodically via hello packets broadcast

## Congestion Control Algorithms
- too many packets in a part of the network
- network throughput plummets due to blocked packets
- 

## Quality of Service

## Internetworking

## Network Layer in Internet

## 



Till Pg 395


