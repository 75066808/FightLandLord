#include "Server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), tcpServer(this)
{
	ui.setupUi(this);
	connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(connectionSlot()));
	tcpServer.listen(QHostAddress::Any, PORT_NUM);
}


void Server::connectionSlot(void)
{
	QTcpSocket *socket = tcpServer.nextPendingConnection();

	if (room.connectSocket(std::shared_ptr<QTcpSocket>(socket)))
	{
		connect(socket, SIGNAL(readyRead()), this, SLOT(serverNotificationSlot()));
		connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectionSlot()));
	}
}

void Server::disconnectionSlot(void)
{
	for (qint32 index = 0;index < 3;index++) // check unconnected
	{
		if (room.checkConnect(index) && room.getSocket(index)->state() == QAbstractSocket::UnconnectedState )
			room.disconnectSocket(index);
	}
}

void Server::serverNotificationSlot(void)
{
	for (qint32 index = 0;index < 3;index++)
	{
		if (!room.checkConnect(index))
			continue;

		QByteArray data = room.getSocket(index)->readAll(); // check all clients

		if (data.isEmpty())
			continue;

		processClientData(index, data);  // deal the special notify
	}
}


void Server::processClientData(qint32 sender, QByteArray &data)
{
	switch (data.at(0))
	{
		case READY: // player ready
			room.ready(sender);
			break;

		case PLAY_CARD: // player plays card
			room.playCard(sender, data.mid(1));
			break;

		case SKIP_CARD: // play skips card
			room.skipCard(sender);
			break;

		case CHOOSE_LANDLORD: // player chooses landlord
			room.chooseLandLord(sender);
			break;

		case SKIP_LANDLORD: // player skips landlord
			room.skipLandLord(sender);
			break;

		default:
			return;
	}

}
