####Assignments
Implement the application layer and simulate the communication process inside the DummynetSL6 VM with customized configurations of bandwidth, packet loss rate and propogation delay time.

---
####Run Program
- UDP_Send_Receive: send & receive JPEG over UDP socket
> - Receiver: `java Receiver <port> <filename>`
> - Sender: `java Receiver localhost <port> <filename>`
- UDP_Stop_And_Wait: implement Stop-and-Wait protocol rdt3.0
> - Receiver: `java Receiver <port> <filename>`
> - Sender: `java Receiver localhost <port> <filename> <timeout>`

---
####Reading List
- J. F. Kurose and K. W. Ross, Computer Networking: A Top-Down Approach (6th Edition), Pearson Education, 2013.
- L. L. Peterson and B. S. Davie, Computer Networks: A Systems Approach (5th Edition), Morgan Kaufmann, 2012.
- A. S. Tanenbaum and D. J. Wetherall, Computer Networks (5th Edition), Pearson Education, 2011.
- [Dummynet Revisited](http://ccr.sigcomm.org/online/files/p13-15v40n2e-carboneA.pdf)
