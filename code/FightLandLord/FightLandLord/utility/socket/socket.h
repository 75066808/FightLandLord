#pragma once
#include <QtNetwork>
#include "../utility/common/common.h"

#define IP_NUM "127.0.0.1"
#define PORT_NUM 6000

class Socket : public QObject {

	Q_OBJECT

public:
	Socket();
	~Socket();


private:
	std::shared_ptr<QTcpSocket> tcpSocket;

signals:
	void socketToModel(std::shared_ptr<Signal> signal);

private slots:
	void modelToSocketSlot(std::shared_ptr<Signal> signal);
	void serverToSocketSlot(void);

};