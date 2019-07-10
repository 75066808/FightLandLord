#pragma once

#include <QtWidgets/QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QThread>

#include "GameRoom.h"
#include "ui_Server.h"

#define PORT_NUM 6000


class Server : public QMainWindow
{
	Q_OBJECT

public:
	Server(QWidget *parent = Q_NULLPTR);
private:
	Ui::ServerClass ui;

	QTcpServer tcpServer;
	GameRoom room;

private slots:
	void connectionSlot(void);
	void disconnectionSlot(void);
	void serverNotificationSlot(void);

private:
	void processClientData(qint32 sender, QByteArray &data);

};
