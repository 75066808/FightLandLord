#pragma once
#include <QDebug>

#include <QtWidgets/QApplication>

#include "../window/window/window.h"
#include "../utility/viewmodel/viewmodel.h"
#include "../utility/common/common.h"
#include "../utility/socket/socket.h"

class App: public QObject
{
	Q_OBJECT;

public:
	App(int argc, char *argv[]);
	~App();

	int run(void);

private:
	QApplication app;
	Window window;
	modelView modelview;
	Socket socket;
};

