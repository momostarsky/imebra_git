/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file tcpSequenceStreamImpl.h
    \brief Declaration of the the TCP stream used by the imebra library.

*/

#if !defined(imebraTcpSequenceStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraTcpSequenceStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include <atomic>
#include <vector>
#include <netdb.h>
#include <condition_variable>
#include <mutex>
#include "baseSequenceStreamImpl.h"

#define IMEBRA_TCP_TIMEOUT_MS 500

namespace imebra
{

namespace implementation
{

long throwTcpException(long socketOperationResult);

///
/// \brief A TCP address.
///
///////////////////////////////////////////////////////////
class tcpAddress
{
public:
    enum class passiveSocket_t: std::uint8_t
    {
        passive,
        active
    };

    tcpAddress(const std::string& node, const std::string& service, passiveSocket_t passiveSocket);
    tcpAddress(const sockaddr& address, socklen_t addressLength);
    ~tcpAddress();

    std::string getNode() const;
    std::string getService() const;
    const sockaddr* getSockAddr() const;
    socklen_t getSockAddrLen() const;
    int getFamily() const;
    int getType() const;
    int getProtocol() const;

private:
    std::string m_node;
    std::string m_service;
    std::vector<std::uint8_t> m_sockAddr;

};


///
/// \brief Used by tcpListener and tcpSequenceStream to
///        perform a graceful termination of blocking
///        methods
///
///////////////////////////////////////////////////////////
class tcpTerminate
{
public:
    ///
    /// \brief Allocate this class at the beginning of a
    ///        blocking method.
    ///
    ///////////////////////////////////////////////////////////
    class tcpTerminateWaiting
    {
    public:
        tcpTerminateWaiting(tcpTerminate& terminateObject);
        ~tcpTerminateWaiting();

        tcpTerminate& m_terminateObject;
    };

    ///
    /// \brief Constructor
    ///
    ///////////////////////////////////////////////////////////
    tcpTerminate();

    ///
    /// \brief Instruct the blocking method to terminate.
    ///
    ///        The blocking method will terminate by throwing
    ///        a StreamClosedException.
    ///
    ///////////////////////////////////////////////////////////
    void terminate();

    ///
    /// \brief If terminate has been called then throws
    ///        StreamClosedException, otherwise returns.
    ///
    ///////////////////////////////////////////////////////////
    void isTerminating();

private:

    std::atomic<bool> m_bTerminate;
    std::atomic<int> m_waiting;
    std::condition_variable m_waitingCondition;
    std::mutex m_waitingMutex;
};

///
/// \brief A TCP socket
///
///////////////////////////////////////////////////////////
class tcpSequenceStream: public baseSequenceStreamInput, public baseSequenceStreamOutput
{
public:

    ///
    /// \brief Constructor.
    ///
    /// \param tcpSocket a TCP socket
    /// \param pAddress  the peer address to which the socket
    ///                  is already connected
    ///
    ///////////////////////////////////////////////////////////
    tcpSequenceStream(int tcpSocket, std::shared_ptr<tcpAddress> pAddress);

    ///
    /// \brief Constructor.
    ///
    /// Creates a socket and connect it to the specified
    /// address. The connection occurs in non-blocking mode
    /// therefore the constructor returns immediately.
    ///
    /// Connection errors are reported at the first call
    /// to read() or write().
    ///
    /// \param pAddress the address to which the socket must
    ///                 be connected
    ///
    ///////////////////////////////////////////////////////////
    tcpSequenceStream(std::shared_ptr<tcpAddress> pAddress);

    ///
    /// \brief Destructor.
    ///
    /// Terminates pending read() and write() operations by
    /// throwing StreamClosedException, shutdown and closes
    /// the socket.
    ///
    ///////////////////////////////////////////////////////////
    ~tcpSequenceStream();

    virtual size_t read(std::uint8_t* pBuffer, size_t bufferLength);
    virtual void write(const std::uint8_t* pBuffer, size_t bufferLength);

    ///
    /// \brief Returns the address to which the socket is
    ///        connected.
    ///
    /// \return the peer's address
    ///
    std::shared_ptr<tcpAddress> getPeerAddress() const;

    ///
    /// \brief Forces a termination of pending and subsequent
    ///        read and write operations by causing them to
    ///        throw SocketClosedException.
    ///
    ///////////////////////////////////////////////////////////
    void terminate();

private:
    int m_socket;
    const std::shared_ptr<tcpAddress> m_pAddress;

    tcpTerminate m_terminate;

};


///
/// \brief Listens for incoming TCP connections.
///
///////////////////////////////////////////////////////////
class tcpListener
{
public:
    ///
    /// \brief Constructors. Creates a socket that listens for
    ///        incoming connections at the specified address.
    ///
    /// \param pAddress the address to which the socket must be
    ///                 bound
    ///
    ///////////////////////////////////////////////////////////
    tcpListener(std::shared_ptr<tcpAddress> pAddress);

    ///
    /// \brief Terminates pending waitForConnection() calls
    ///        and closes the socket.
    ///
    ///////////////////////////////////////////////////////////
    ~tcpListener();

    ///
    /// \brief Forces the termination of pending
    ///        waitForConnection() calls.
    ///
    ///////////////////////////////////////////////////////////
    void terminate();

    ///
    /// \brief Wait for an incoming connection until a
    ///        connection is accepted or the socket is
    ///        terminated by the destructor or terminate(),
    ///        in which case it throws SocketClosedError.
    ///
    /// \return an tcpSequenceStream for to the accepted
    ///         connection
    ///
    ///////////////////////////////////////////////////////////
    std::shared_ptr<tcpSequenceStream> waitForConnection();

private:
    int m_socket;

    tcpTerminate m_terminate;
};


} // namespace implementation

} // namespace imebra


#endif // !defined(imebraTcpSequenceStream_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
