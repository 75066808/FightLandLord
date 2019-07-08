#include "Server.h"

Server::Server(QWidget *parent) : QMainWindow(parent), tcpServer(this)
{
	ui.setupUi(this);
	connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	tcpServer.listen(QHostAddress::Any, PORT_NUM);
}


void Server::acceptConnection(void)
{
	QTcpSocket *socket = tcpServer.nextPendingConnection();
	if (room.connectSocket(socket))
	{
		connect(socket, SIGNAL(readyRead()), this, SLOT(readClientData()));
		connect(socket, SIGNAL(disconnect()), this, SLOT(dealDisconnection()));
	}
}

void Server::dealDisconnection(void)
{
	for (qint32 index = 0;index < 3;index++)
	{
		if (room.getSocket(index)->state() == QAbstractSocket::UnconnectedState && room.checkConnect(index))
			room.disconnectSocket(index);
	}
}

void Server::readClientData(void)
{
	for (qint32 index = 0;index < 3;index++)
	{
		if (!room.checkConnect(index))
			continue;

		QByteArray data = room.getSocket(index)->readAll(); // check all clients

		if (data.isEmpty())
			continue;

		dealClientData(index, data);  // deal the special notify
	}
}




void Server::dealClientData(qint32 sender, QByteArray &data)
{
	QByteArray transData;

	qint8 signalType = data[0];
	qint8 signalContent = data[1];

	switch (signalType)
	{

	case BROADCAST:
		switch (signalContent)
		{
		case READY: // player ready
			room.readyStart(sender);
			break;

		case PLAY_CARD: // player plays card
			room.playCard(sender);
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
		break;

	case ALL_FINISH:
		switch (signalContent)
		{
		case READY: // player ready
			room.readyFinish();
			break;

		case PLAY_CARD: // player plays card
		case SKIP_CARD: // play skips card
			room.playNextTurn();
			break;

		case CHOOSE_LANDLORD: // player chooses landlord
		case SKIP_LANDLORD: // player skips landlord
			room.chooseNextTurn();
			break;

		case DEAL_CARD: // player deals card
			room.dealCardFinish();
			break;
		case DEAL_LANDLORD: // player deals landlord card
			room.dealLandLordFinish();
			break;

		default:
			return;
		}
		break;
	
	}

}
