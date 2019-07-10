#include "app.h"



App::App(int argc, char *argv[]): app(argc, argv)
{
	std::shared_ptr<Player> player1 = std::make_shared<Player>();
	std::shared_ptr<Player> player2 = std::make_shared<Player>();
	std::shared_ptr<Player> player3 = std::make_shared<Player>();
	std::shared_ptr<Table> table = std::make_shared<Table>();

	modelview.setSelf(player2);
	modelview.setUpper(player1);
	modelview.setLower(player3);
	modelview.setTable(table);

	player1->setStatus(-1);
	player2->setStatus(-2);
	player3->setStatus(-3);

	const qint8* tmp = modelview.getSelfOnHand()->getArr();
	window.setCurrentCardsInHand(tmp);

	connect(&modelview, SIGNAL(viewModelToWindowSignal(std::shared_ptr<Signal>)),
		&window, SLOT(viewModelToWindowSlot(std::shared_ptr<Signal>)));

	connect(&window, SIGNAL(windowToViewModelSignal(std::shared_ptr <Signal>)),
		&modelview, SLOT(windowToViewModelSlot(std::shared_ptr<Signal>)));

	connect(&*player1, SIGNAL(modelToSocketSignal(std::shared_ptr<Signal>)),
		&socket, SLOT(modelToSocketSlot(std::shared_ptr<Signal>)));

	connect(&*player2, SIGNAL(modelToSocketSignal(std::shared_ptr<Signal>)),
		&socket, SLOT(modelToSocketSlot(std::shared_ptr<Signal>)));

	connect(&*player3, SIGNAL(modelToSocketSignal(std::shared_ptr<Signal>)),
		&socket, SLOT(modelToSocketSlot(std::shared_ptr<Signal>)));

	connect(&*table, SIGNAL(modelToSocketSignal(std::shared_ptr<Signal>)),
		&socket, SLOT(modelToSocketSlot(std::shared_ptr<Signal>)));

	connect(&socket, SIGNAL(socketToModel(std::shared_ptr<Signal>)),
		&*player1, SLOT(socketToModelSlot(std::shared_ptr<Signal>)));

	connect(&socket, SIGNAL(socketToModel(std::shared_ptr<Signal>)),
		&*player2, SLOT(socketToModelSlot(std::shared_ptr<Signal>)));

	connect(&socket, SIGNAL(socketToModel(std::shared_ptr<Signal>)),
		&*player3, SLOT(socketToModelSlot(std::shared_ptr<Signal>)));

	connect(&socket, SIGNAL(socketToModel(std::shared_ptr<Signal>)),
		&*table, SLOT(socketToModelSlot(std::shared_ptr<Signal>)));

}

App::~App()
{

}

int App::run(void)
{
	window.show();
	return app.exec();
}
