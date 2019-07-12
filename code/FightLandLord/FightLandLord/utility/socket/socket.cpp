#include "socket.h"

Socket::Socket(): tcpSocket(std::make_shared<QTcpSocket>())
{
	connect(&*tcpSocket, SIGNAL(readyRead()), this, SLOT(socketNotificationSlot()));
}

Socket::~Socket()
{

}



void Socket::socketCommandSlot(std::shared_ptr<Signal> signal)
{
	QByteArray data;

	qDebug() << "Model to Socket" << endl;

	switch (signal->signalType)
	{
	case CONNECT:
		tcpSocket->abort(); // disconnect current connection
		tcpSocket->connectToHost(QHostAddress(IP_NUM), PORT_NUM); // send connect request
		break;
	case DISCONNECT:
		tcpSocket->disconnectFromHost(); // disconnect from host
		emit socketNotificationSignal(signal);
		break;
	default:
		data[0] = signal->signalType;
		data.append(signal->cardTransfer);
		tcpSocket->write(data); // transfer to server
		break;
	}
}

void Socket::socketNotificationSlot(void)
{
	qDebug() << "Server to Socket" << endl;
	QByteArray data = tcpSocket->readAll(); // read from server
	QByteArray temp;

	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->playerType[0] = data[0];
	signal->playerType[1] = data[1];
	signal->playerType[2] = data[2];

	signal->signalType = data[3];

	for (qint32 i = 4;i < data.size();i++)
		temp[i - 4] = data[i];

	signal->cardTransfer = temp;
	emit socketNotificationSignal(signal);
}