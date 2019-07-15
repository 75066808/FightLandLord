#pragma once
#include <QtNetwork>
#include "../utility/common/common.h"

#define IP_NUM "117.78.3.84"
#define PORT_NUM 6000

class Socket : public QObject {

	Q_OBJECT

public:
	Socket();
	~Socket();


private:
	std::shared_ptr<QTcpSocket> tcpSocket;

signals:
	void socketNotificationSignal(std::shared_ptr<Signal> signal);

private slots:
	void socketCommandSlot(std::shared_ptr<Signal> signal);
	void socketNotificationSlot(void);

};