/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file tcpSequenceStreamImpl.cpp
    \brief Implementation of the the TCP stream used by the imebra library.

*/

#include "tcpSequenceStreamImpl.h"
#include "../include/imebra/exceptions.h"
#include <string.h>

#ifdef IMEBRA_WINDOWS

#include <Ws2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#endif


namespace imebra
{

namespace implementation
{

#ifdef IMEBRA_WINDOWS

//
// Force the Winsock initialization
//  starts.
//
///////////////////////////////////////////////////////////
static initWinsock::forceWinsockInitialization forceInitialization;

initWinsock::initWinsock()
{
    IMEBRA_FUNCTION_START();

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        IMEBRA_THROW(std::runtime_error, "WSA socket initialization failure");
    }

    IMEBRA_FUNCTION_END();
}

initWinsock::~initWinsock()
{
    WSACleanup();
}

std::shared_ptr<initWinsock> initWinsock::getWinsockInitialization()
{
    IMEBRA_FUNCTION_START();

    // Violation to requirement REQ_MAKE_SHARED due to protected constructor
    static std::shared_ptr<initWinsock> m_initWinsock(std::make_shared<initWinsock>());

    return m_initWinsock;

    IMEBRA_FUNCTION_END();
}

#endif


///////////////////////////////////////////////////////////
//
// SocketTimeout is used only internally when a TCP
//  timeout is detected
//
///////////////////////////////////////////////////////////
class SocketTimeout: public  std::runtime_error
{
public:
    SocketTimeout(const std::string& message):
        std::runtime_error(message)
    {
    }
};


///////////////////////////////////////////////////////////
//
// Throw an exception according to the result of a socket
//  operation and the content of errno
//
///////////////////////////////////////////////////////////
long throwTcpException(long socketOperationResult)
{
    IMEBRA_FUNCTION_START();

    if(socketOperationResult >= 0)
    {
        return socketOperationResult;
    }

#ifdef IMEBRA_WINDOWS
    switch(WSAGetLastError())
    {
    case WSAECONNREFUSED:
        IMEBRA_THROW(TCPConnectionRefused, "Connection refused");
    case WSAENOBUFS:
    case WSAEMFILE:
        throw std::bad_alloc();
    case WSAEINPROGRESS:
        return socketOperationResult;
    case WSAEFAULT:
        IMEBRA_THROW(std::logic_error, "Invalid address space");
    case WSAEACCES:
        IMEBRA_THROW(PermissionDeniedError, "Permission denied");
    case WSAEINVAL:
        IMEBRA_THROW(std::logic_error, "Invalid argument");
    case WSAENOTSOCK:
        IMEBRA_THROW(std::logic_error, "Operation on invalid socket");
    case WSAEWOULDBLOCK:
        IMEBRA_THROW(SocketTimeout, "Timed out");
    case EPIPE:
        IMEBRA_THROW(StreamClosedError, "Socket closed");
    case WSAEADDRINUSE:
        IMEBRA_THROW(TCPAddressAlreadyInUse, "The specified address is already in use.");

    }
#else
    int error = errno;
    switch(error)
    {
    case ECONNREFUSED:
        IMEBRA_THROW(TCPConnectionRefused, "Connection refused")
    case ENOBUFS:
    case ENOMEM:
    case EMFILE:
        throw std::bad_alloc();
    case EINPROGRESS:
        return socketOperationResult;
    case EFAULT:
        IMEBRA_THROW(std::logic_error, "Invalid address space");
    case EACCES:
        IMEBRA_THROW(PermissionDeniedError, "Permission denied");
    case EINVAL:
        IMEBRA_THROW(std::logic_error, "Invalid argument");
    case ENOTSOCK:
        IMEBRA_THROW(std::logic_error, "Operation on invalid socket");
    case EWOULDBLOCK:
        IMEBRA_THROW(SocketTimeout, "Timed out");
    case EPIPE:
        IMEBRA_THROW(StreamClosedError, "Socket closed");
    case EADDRINUSE:
        IMEBRA_THROW(TCPAddressAlreadyInUse, "The specified address is already in use.")
    }
#endif
    throw;

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Throw an exception based on the result of a tcp
//  addr operation
//
///////////////////////////////////////////////////////////
void throwAddrException(int addrOperationResult)
{
    IMEBRA_FUNCTION_START();

    if(addrOperationResult == 0)
    {
        return;
    }

    const char* errorDescription = gai_strerror(addrOperationResult);

    switch(addrOperationResult)
    {
    case EAI_AGAIN:
        IMEBRA_THROW(AddressTryAgainError, errorDescription);
    case EAI_FAIL:
        IMEBRA_THROW(AddressError, errorDescription);
    case EAI_MEMORY:
        throw std::bad_alloc();
    case EAI_NONAME:
        IMEBRA_THROW(AddressNoNameError, errorDescription);
    case EAI_SERVICE:
        IMEBRA_THROW(AddressServiceNotSupportedError, errorDescription);
#ifndef IMEBRA_WINDOWS
    case EAI_SYSTEM:
        throwTcpException(-1);
#endif
    default:
        IMEBRA_THROW(std::logic_error, errorDescription);
    }

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// tcpAddress constructors
//
///////////////////////////////////////////////////////////
tcpAddress::tcpAddress(const std::string& node, const std::string& service, passiveSocket_t passiveSocket):
    m_node(node),
    m_service(service)
{
    IMEBRA_FUNCTION_START();

    addrinfo hints;
    ::memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = (passiveSocket == passiveSocket_t::passive ? AI_PASSIVE : 0);

    const char* pNode(node.empty() ? 0 : node.c_str());
    const char* pService(service.empty() ? 0 : service.c_str());
    addrinfo* address(0);
    throwTcpException(getaddrinfo(pNode, pService, &hints, &address));

    m_sockAddr.resize(address->ai_addrlen);
    ::memcpy(&(m_sockAddr[0]), address->ai_addr, address->ai_addrlen);
    freeaddrinfo(address);

    IMEBRA_FUNCTION_END();
}

tcpAddress::tcpAddress(const sockaddr& address, socklen_t addressLength)
{
    IMEBRA_FUNCTION_START();

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    throwTcpException(getnameinfo(&address, addressLength, host, sizeof(host), service, sizeof(service), 0));

    m_sockAddr.resize(addressLength);
    ::memcpy(&(m_sockAddr[0]), &address, addressLength);
    m_node = host;
    m_service = service;

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpAddress::~tcpAddress()
{
}


///////////////////////////////////////////////////////////
//
// Return the node part of the address
//
///////////////////////////////////////////////////////////
std::string tcpAddress::getNode() const
{
    return m_node;
}


///////////////////////////////////////////////////////////
//
// Return the service part of the address
//
///////////////////////////////////////////////////////////
std::string tcpAddress::getService() const
{
    return m_service;
}


///////////////////////////////////////////////////////////
//
// Return a sockaddr structure representing the address
// The structure is owned by tcpAddress.
//
///////////////////////////////////////////////////////////
const sockaddr* tcpAddress::getSockAddr() const
{
    return (const sockaddr*)(m_sockAddr.data());
}


///////////////////////////////////////////////////////////
//
// Return the length of the structure returned by
//  getSockAddr().
//
///////////////////////////////////////////////////////////
socklen_t tcpAddress::getSockAddrLen() const
{
    return (socklen_t)m_sockAddr.size();
}


///////////////////////////////////////////////////////////
//
// Return the address' family.
//
///////////////////////////////////////////////////////////
int tcpAddress::getFamily() const
{
    return AF_INET;
}


///////////////////////////////////////////////////////////
//
// Return the address' type
//
///////////////////////////////////////////////////////////
int tcpAddress::getType() const
{
    return SOCK_STREAM;
}


///////////////////////////////////////////////////////////
//
// Return the address' protocol
//
///////////////////////////////////////////////////////////
int tcpAddress::getProtocol() const
{
    return IPPROTO_TCP;
}


///////////////////////////////////////////////////////////
//
// Class used to coordinate a graceful termination of
// long running functions (listen read and write)
//
///////////////////////////////////////////////////////////
tcpTerminate::tcpTerminateWaiting::tcpTerminateWaiting(tcpTerminate& terminateObject):
    m_terminateObject(terminateObject)
{
    IMEBRA_FUNCTION_START();

    std::unique_lock<std::mutex> lock(m_terminateObject.m_waitingMutex);
    if(m_terminateObject.m_bTerminate.load())
    {
        IMEBRA_THROW(StreamClosedError, "The socket has been closed");
    }
    std::atomic_fetch_add(&(m_terminateObject.m_waiting), 1);

    IMEBRA_FUNCTION_END();
}

tcpTerminate::tcpTerminateWaiting::~tcpTerminateWaiting()
{
    std::unique_lock<std::mutex> lock(m_terminateObject.m_waitingMutex);
    std::atomic_fetch_sub(&(m_terminateObject.m_waiting), 1);
    m_terminateObject.m_waitingCondition.notify_all();
}

tcpTerminate::tcpTerminate():
    m_bTerminate(false), m_waiting(0)
{
}

void tcpTerminate::terminate()
{
    m_bTerminate.store(true);
    std::unique_lock<std::mutex> lock(m_waitingMutex);
    while(m_waiting.load() > 0)
    {
        m_waitingCondition.wait(lock);
    }
}

void tcpTerminate::isTerminating()
{
    IMEBRA_FUNCTION_START();

    if(m_bTerminate.load())
    {
        throw StreamClosedError("The socket has been closed");
    }

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// TCP I/O class constructors
//
///////////////////////////////////////////////////////////
tcpSequenceStream::tcpSequenceStream(int tcpSocket, std::shared_ptr<tcpAddress> pAddress):
    m_socket(tcpSocket),
    m_pAddress(pAddress)
{
    IMEBRA_FUNCTION_START();

    // Enable blocking mode
    int flags = (int)throwTcpException(fcntl(m_socket, F_GETFL, 0));
    throwTcpException(fcntl(m_socket, F_SETFL, flags & ~O_NONBLOCK));

    // Set timeout
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = IMEBRA_TCP_TIMEOUT_MS * 1000;
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    IMEBRA_FUNCTION_END();
}

tcpSequenceStream::tcpSequenceStream(std::shared_ptr<tcpAddress> pAddress):
    m_socket((int)throwTcpException(socket(pAddress->getFamily(), pAddress->getType(), pAddress->getProtocol()))),
    m_pAddress(pAddress)
{
    IMEBRA_FUNCTION_START();

#if !defined(IMEBRA_WINDOWS) && (__linux__ != 1)
    // Disable SIGPIPE
    int sigpipe = 1;
    setsockopt(sd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&sigpipe, sizeof(sigpipe));
#endif

    // Connect in non-blocking mode, then enable blocking
    int flags = (int)throwTcpException(fcntl(m_socket, F_GETFL, 0));
    throwTcpException(fcntl(m_socket, F_SETFL, flags | O_NONBLOCK));

    throwTcpException(connect(m_socket, pAddress->getSockAddr(), pAddress->getSockAddrLen()));

    throwTcpException(fcntl(m_socket, F_SETFL, flags & ~O_NONBLOCK));

    // Set timeout
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = IMEBRA_TCP_TIMEOUT_MS * 1000;
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Trigger the termination of the read and write operations
//
///////////////////////////////////////////////////////////
void tcpSequenceStream::terminate()
{
    m_terminate.terminate();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpSequenceStream::~tcpSequenceStream()
{
    terminate();

    shutdown(m_socket, SHUT_RDWR);
    close(m_socket);
}


///////////////////////////////////////////////////////////
//
// Read from TCP stream
//
///////////////////////////////////////////////////////////
size_t tcpSequenceStream::read(std::uint8_t* pBuffer, size_t bufferLength)
{
    IMEBRA_FUNCTION_START();

    tcpTerminate::tcpTerminateWaiting waiting(m_terminate);

    // A peer shutdown causes the reception of a zero
    // bytes buffer
    ///////////////////////////////////////////////////////////
    if(bufferLength == 0)
    {
        m_terminate.isTerminating();
        return 0;
    }

    // Wait for data. Exit only when data arrives or the
    // termination is triggered
    ///////////////////////////////////////////////////////////
    for(;;)
    {
        m_terminate.isTerminating();

        try
        {
            long receivedBytes(throwTcpException(recv(m_socket, pBuffer, bufferLength, 0)));
            if(receivedBytes == 0)
            {
                return 0;
            }
            else
            {
                return (size_t)receivedBytes;
            }
        }
        catch(const SocketTimeout&)
        {
            // Socket time out. Retry
        }
    }

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Write into the TCP stream
//
///////////////////////////////////////////////////////////
void tcpSequenceStream::write(const std::uint8_t* pBuffer, size_t bufferLength)
{
    IMEBRA_FUNCTION_START();

    tcpTerminate::tcpTerminateWaiting waiting(m_terminate);

    // Don't send zero bytes buffer (this is done via shutdown)
    ///////////////////////////////////////////////////////////
    if(bufferLength == 0)
    {
        return;
    }

    // Loop until the data is sent or the termination is
    // triggered
    ///////////////////////////////////////////////////////////
    for(size_t totalSentBytes(0); totalSentBytes != bufferLength; /* incremented in the loop */)
    {
        try
        {
            m_terminate.isTerminating();

#if (__linux__ == 1)
            long sentBytes = throwTcpException((long)send(m_socket, pBuffer + totalSentBytes, bufferLength - totalSentBytes, MSG_NOSIGNAL));
#else
            long sentBytes = throwTcpException((long)send(m_socket, pBuffer + totalSentBytes, bufferLength - totalSentBytes, 0));
#endif

            totalSentBytes += (size_t)sentBytes;
        }
        catch(const SocketTimeout&)
        {
            // Socket timeout. Retry
        }
    }

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Get the address of the connected peer
//
///////////////////////////////////////////////////////////
std::shared_ptr<tcpAddress> tcpSequenceStream::getPeerAddress() const
{
    return m_pAddress;
}


///////////////////////////////////////////////////////////
//
// TCP listener constructor
//
///////////////////////////////////////////////////////////
tcpListener::tcpListener(std::shared_ptr<tcpAddress> pAddress):
    m_socket((int)throwTcpException(socket(pAddress->getFamily(), pAddress->getType(), pAddress->getProtocol())))
{
    IMEBRA_FUNCTION_START();

    // Connect in non-blocking mode, then enable blocking
    int flags = (int)throwTcpException(fcntl(m_socket, F_GETFL, 0));
    throwTcpException(fcntl(m_socket, F_SETFL, flags | O_NONBLOCK));

    throwTcpException(bind(m_socket, pAddress->getSockAddr(), pAddress->getSockAddrLen()));
    throwTcpException(listen(m_socket, SOMAXCONN));

    throwTcpException(fcntl(m_socket, F_SETFL, flags & ~O_NONBLOCK));

    // Set timeout
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;
    throwTcpException(setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)));
    throwTcpException(setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)));

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Trigger the listener's termination
//
///////////////////////////////////////////////////////////
void tcpListener::terminate()
{
    m_terminate.terminate();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpListener::~tcpListener()
{
    terminate();
    ::close(m_socket);
}


///////////////////////////////////////////////////////////
//
// Listen for incoming connections and accepts them
//
///////////////////////////////////////////////////////////
std::shared_ptr<tcpSequenceStream> tcpListener::waitForConnection()
{
    IMEBRA_FUNCTION_START();

    tcpTerminate::tcpTerminateWaiting waiting(m_terminate);

    // Wait for connections until terminated
    ///////////////////////////////////////////////////////////
    for(;;)
    {
        m_terminate.isTerminating();

        sockaddr_in addr;
        socklen_t sockaddrLen(sizeof(addr));
        try
        {
            int acceptedSocket = (int)throwTcpException(accept(m_socket, (sockaddr*)&addr, &sockaddrLen));

            std::shared_ptr<tcpAddress> pPeerAddress(std::make_shared<tcpAddress>(*((sockaddr*)&addr), sockaddrLen));
            return std::make_shared<tcpSequenceStream>(acceptedSocket, pPeerAddress);
        }
        catch(const SocketTimeout&)
        {
            // Timed out. retry
        }
    }

    IMEBRA_FUNCTION_END();
}


} // namespace implementation

} // namespace imebra


