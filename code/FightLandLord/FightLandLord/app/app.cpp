#include "app.h"



App::App(int argc, char *argv[]): app(argc, argv)
{
	std::shared_ptr<Player> player1 = std::make_shared<Player>();
	std::shared_ptr<Player> player2 = std::make_shared<Player>();
	std::shared_ptr<Player> player3 = std::make_shared<Player>();
	std::shared_ptr<Socket> socket = std::make_shared<Socket>();

	modelview.setSelf(player2);
	modelview.setUpper(player1);
	modelview.setLower(player3);
	modelview.setSocket(socket);

	player1->setStatus(UPPER_DIS_CONNECT);
	player2->setStatus(SELF_DIS_CONNECT);
	player3->setStatus(LOWER_DIS_CONNECT);
	player1->setOnTable(player2->getOnTable());
	player3->setOnTable(player2->getOnTable());


	window.setOnHandNum(modelview.getOnHandNum());
	window.setOnHandCard(modelview.getOnHandCard());

	window.setSelfHandOutNum(modelview.getSelfHandOutNum());
	window.setSelfHandOut(modelview.getSelfHandOut());
	window.setOnHandSelected(modelview.getOnHandSelected());
	window.setStatus(modelview.getStatus());

	window.setLowerNum(modelview.getLowerNum());
	window.setLowerCard(modelview.getLowerCard());
	window.setLowerHandOutNum(modelview.getLowerHandOutNum());
	window.setLowerHandOut(modelview.getLowerHandOut());
	window.setLowerStatus(modelview.getLowerStatus());

	window.setUpperNum(modelview.getUpperNum());
	window.setUpperCard(modelview.getUpperCard());
	window.setUpperHandOutNum(modelview.getUpperHandOutNum());
	window.setUpperHandOut(modelview.getUpperHandOut());
	window.setUpperStatus(modelview.getUpperStatus());

	window.setLandLordNum(modelview.getLandLordNum());
	window.setLandLordCard(modelview.getLandLordCard());

	connect(&modelview, SIGNAL(viewModelNotificationSignal(std::shared_ptr<Signal>)),
		&window, SLOT(windowNotificationSlot(std::shared_ptr<Signal>)));

	connect(&window, SIGNAL(windowCommandSignal(std::shared_ptr<Signal>)),
		&modelview, SLOT(viewModelCommandSlot(std::shared_ptr<Signal>)));

	window.initWindow();
}

App::~App()
{

}

int App::run(void)
{
	window.show();
	return app.exec();
}
