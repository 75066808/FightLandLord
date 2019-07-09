#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// this->Scene = new QGraphicsScene(ui->graphicsView);

	// this->cardTempPixmapItem = new QGraphicsPixmapItem();

	// this->cardTempPixmap = new QPixmap();

	connect(ui.btnShowCard, SIGNAL(clicked()), this, SLOT(showCardsInHand()));

}

void Window::showCardsInHand()
{
	// QPainter cardPainter;
	//QImage *cardTempImg = new QImage();
	QPixmap *cardTempPixmap = new QPixmap();
	//QGraphicsPixmapItem* cardTempPixmapItem = new QGraphicsPixmapItem();
	//QRect sceneRect;
	//QSize rectSize;
	//QPoint rectTopLeftPoint;
	QGraphicsScene *Scene = new QGraphicsScene(ui.graphicsView);

	//rectSize.setHeight(200);
	//rectSize.setWidth(200);
	//rectTopLeftPoint.setX(20);
	//rectTopLeftPoint.setY(20);
	//sceneRect.setSize(rectSize);
	//sceneRect.setTopLeft(rectTopLeftPoint);


	

	//cardTempImg->load("joker", "jpg");
	//*cardTempPixmap = QPixmap::fromImage(*cardTempImg);

	//cardTempPixmap->load("joker", "jpg");
	//cardTempPixmapItem->setPixmap(*cardTempPixmap);
	//cardTempPixmapItem->setPos(20, 20);

	Scene->setSceneRect(300, -100, 1, 1);
	addCardInScene(10, 10, cardTempPixmap, Scene);
	addCardInScene(30, 10, cardTempPixmap, Scene);

	//Scene->addItem(cardTempPixmapItem);

	//Scene->addPixmap(*cardTempPixmap)->setPos(10,10);

	//Scene->addPixmap(QPixmap::fromImage(*cardTempImg));

	//cardTempPixmap->load("spadeK", "jpg");
	//Scene->addPixmap(*cardTempPixmap)->setPos(30,10);

	//Scene->addText("Hello World!");
	//ui->graphicsView->setSceneRect(sceneRect);

	ui.graphicsView->setScene(Scene);
	
	ui.graphicsView->show();

	//delete cardTempPixmap;
	//delete cardTempPixmapItem;
	//delete Scene;

}


void Window::addCardInScene(qreal x, qreal y, QPixmap* cardTempPixmap, QGraphicsScene* Scene)
{
	cardTempPixmap->load("poker_resource/joker1", "jpg");
	Scene->addPixmap(*cardTempPixmap)->setPos(x, y);

}

