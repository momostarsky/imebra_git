TCP classes
============================

The TCP classes can be used with :cpp:class:`ImebraStreamWriter` and :cpp:class:`ImebraStreamReader` to
send and receive data through a TCP stream.

A TCP server socket (a socket that listen for incoming connection) can be realized with the class
:cpp:class:`ImebraTCPListener`, while a TCP client (a socket that initiates a connection with a
server) can be realized with the class :cpp:class:`ImebraTCPStream`.

:cpp:class:`ImebraTCPListener` creates a new :cpp:class:`ImebraTCPStream` for each accepted incoming connection.

Both :cpp:class:`ImebraTCPListener` and :cpp:class:`ImebraTCPStream` expose blocking methods (except for
the constructors which connect to the peer in non-blocking mode).
You can exit a blocking method to terminate by closing the socket or by calling the terminate() method.


ImebraTCPAddress
----------------
.. doxygenclass:: ImebraTCPAddress
   :members:

ImebraTCPActiveAddress
----------------------
.. doxygenclass:: ImebraTCPActiveAddress
   :members:

ImebraTCPPassiveAddress
-----------------------
.. doxygenclass:: ImebraTCPPassiveAddress
   :members:

ImebraTCPStream
---------------
.. doxygenclass:: ImebraTCPStream
   :members:

ImebraTCPListener
-----------------
.. doxygenclass:: ImebraTCPListener
   :members:
