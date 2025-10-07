#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    bool startServer(const QString &localIp, quint16 localPort, QString &err);
    void stopServer();
    void connectToPeer(const QString &peerIp, quint16 peerPort, QString &err);
    void disconnectFromPeer();
    bool sendLine(const QString &line, QString &err);
    bool isConnected() const;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &msg);
    void errorOccurred(const QString &err);

private slots: // Qt5 needs slots for SIGNAL/SLOT syntax
    void onSocketReadyRead();
    void onSocketDisconnected();
    void onSocketErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    void closeSocket();
    void onNewConnection();

    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QByteArray m_inBuffer;
};
