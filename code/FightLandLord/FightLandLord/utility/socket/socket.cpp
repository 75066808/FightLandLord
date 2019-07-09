#include "socket.h"

Socket::Socket(): tcpSocket(std::make_shared<QTcpSocket>())
{
	connect(&*tcpSocket, SIGNAL(readyRead()), this, SLOT(serverToSocketSlot()));
}

Socket::~Socket()
{

}



void Socket::modelToSocketSlot(std::shared_ptr<Signal> signal)
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
		break;
	default:
		if (signal->valid != 0) // valid signal
		{
			data[0] = signal->signalType;
			data.append(signal->cardTransfer.tranToSig());
			tcpSocket->write(data); // transfer to server
			
		}
		break;
	}
}

void Socket::serverToSocketSlot(void)
{
	qDebug() << "Server to Socket" << endl;
	QByteArray data = tcpSocket->readAll(); // read from server
	QByteArray temp;

	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->playerType = data[0];
	signal->signalType = data[1];

	for (qint32 i = 2;i < data.size();i++)
		temp[i - 2] = data[i];

	signal->cardTransfer = temp;
	emit socketToModel(signal);
}