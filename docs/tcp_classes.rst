TCP classes
============================

The TCP classes can be used with :cpp:class:`dicomhero::StreamWriter` and :cpp:class:`dicomhero::StreamReader` to
send and receive data through a TCP stream.

A TCP server socket (a socket that listen for incoming connection) can be realized with the class
:cpp:class:`dicomhero::TCPListener`, while a TCP client (a socket that initiates a connection with a
server) can be realized with the class :cpp:class:`dicomhero::TCPStream`.

:cpp:class:`dicomhero::TCPListener` creates a new :cpp:class:`dicomhero::TCPStream` for each accepted incoming connection.

Both :cpp:class:`dicomhero::TCPListener` and :cpp:class:`dicomhero::TCPStream` expose blocking methods (except for
the constructors which connect to the peer in non-blocking mode).
You can exit a blocking method to terminate by closing the socket or by calling the terminate() method.


