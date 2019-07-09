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

	cardTempPixmap->load("joker", "jpg");
	//cardTempPixmapItem->setPixmap(*cardTempPixmap);
	//cardTempPixmapItem->setPos(20, 20);

	Scene->setSceneRect(-300, 100, 1, 1);
	//Scene->addItem(cardTempPixmapItem);
	Scene->addPixmap(*cardTempPixmap);
	//Scene->addPixmap(QPixmap::fromImage(*cardTempImg));

	//Scene->addText("Hello World!");
	//ui->graphicsView->setSceneRect(sceneRect);
	ui.graphicsView->setScene(Scene);

	//ui.graphicsView->show();

	//delete cardTempPixmap;
	//delete cardTempPixmapItem;
	//delete Scene;

}
