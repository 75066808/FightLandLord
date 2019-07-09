#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	connect(ui.btnShowCard, SIGNAL(clicked()), this, SLOT(showCardsInHand()));

}

void Window::showCardsInHand()
{

	QPixmap *cardTempPixmap = new QPixmap();

	QGraphicsScene *Scene = new QGraphicsScene();

	qreal init_x = 10;
	qreal init_y = 10;
	
	int cardNum = 15;




	Scene->setSceneRect(300, -100, 1, 1);


	for (size_t i = 0; i < cardNum; i++)
	{
		addCardInScene(init_x + i*20, init_y, cardTempPixmap, Scene);
	}




	ui.graphicsView->setScene(Scene);
	
	ui.graphicsView->show();




}



void Window::addCardInScene(qreal x, qreal y, QPixmap* cardTempPixmap, QGraphicsScene* Scene)
{
	cardTempPixmap->load("poker_resource/joker1", "jpg");
	Scene->addPixmap(*cardTempPixmap)->setPos(x, y);

}


