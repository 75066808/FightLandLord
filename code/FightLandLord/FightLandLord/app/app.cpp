#include "app.h"



App::App(int argc, char *argv[]): app(argc, argv)
{
	std::shared_ptr<Player> player1 = std::make_shared<Player>();
	std::shared_ptr<Player> player2 = std::make_shared<Player>();
	std::shared_ptr<Player> player3 = std::make_shared<Player>();
	std::shared_ptr<Table> table = std::make_shared<Table>();
	std::shared_ptr<Socket> socket = std::make_shared<Socket>();

	modelview.setSelf(player2);
	modelview.setUpper(player1);
	modelview.setLower(player3);
	modelview.setTable(table);
	modelview.setSocket(socket);

	player1->setStatus(-1);
	player2->setStatus(-2);
	player3->setStatus(-3);

	window.setOnHandNum(modelview.getOnHandNum());
	window.setOnHandCard(modelview.getOnHandCard());
	window.setOnHandSelected(modelview.getOnHandSelected());
	window.setLowerNum(modelview.getLowerNum());
	window.setLowerCard(modelview.getLowerCard());
	window.setUpperNum(modelview.getUpperNum());
	window.setUpperCard(modelview.getUpperCard());
	window.setOnTableNum(modelview.getOnTableNum());
	window.setOnTableCard(modelview.getOnTableCard());
	window.setLandLordNum(modelview.getLandLordNum());
	window.setLandLordCard(modelview.getLandLordCard());

	connect(&modelview, SIGNAL(viewModelNotificationSignal(std::shared_ptr<Signal>)),
		&window, SLOT(windowNotificationSlot(std::shared_ptr<Signal>)));

	connect(&window, SIGNAL(windowCommandSignal(std::shared_ptr<Signal>)),
		&modelview, SLOT(viewModelCommandSlot(std::shared_ptr<Signal>)));



}

App::~App()
{

}

int App::run(void)
{
	window.show();
	return app.exec();
}
