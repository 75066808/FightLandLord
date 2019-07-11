#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(buttonClick()));
	
	scene.setSceneRect(0, 0, 1, 1);
	pixmap[0][3].load("poker_resource/club3", "jpg");
	pixmap[0][4].load("poker_resource/club4", "jpg");
	pixmap[0][5].load("poker_resource/club5", "jpg");
	pixmap[0][6].load("poker_resource/club6", "jpg");
	pixmap[0][7].load("poker_resource/club7", "jpg");
	pixmap[0][8].load("poker_resource/club8", "jpg");
	pixmap[0][9].load("poker_resource/club9", "jpg");
	pixmap[0][10].load("poker_resource/club10", "jpg");
	pixmap[0][11].load("poker_resource/clubJ", "jpg");
	pixmap[0][12].load("poker_resource/clubQ", "jpg");
	pixmap[0][13].load("poker_resource/clubK", "jpg");
	pixmap[0][14].load("poker_resource/clubA", "jpg");
	pixmap[0][15].load("poker_resource/club2", "jpg");
	pixmap[0][16].load("poker_resource/joker1", "jpg");
	pixmap[0][17].load("poker_resource/joker2", "jpg");

	pixmap[1][3].load("poker_resource/heart3", "jpg");
	pixmap[1][4].load("poker_resource/heart4", "jpg");
	pixmap[1][5].load("poker_resource/heart5", "jpg");
	pixmap[1][6].load("poker_resource/heart6", "jpg");
	pixmap[1][7].load("poker_resource/heart7", "jpg");
	pixmap[1][8].load("poker_resource/heart8", "jpg");
	pixmap[1][9].load("poker_resource/heart9", "jpg");
	pixmap[1][10].load("poker_resource/heart10", "jpg");
	pixmap[1][11].load("poker_resource/heartJ", "jpg");
	pixmap[1][12].load("poker_resource/heartQ", "jpg");
	pixmap[1][13].load("poker_resource/heartK", "jpg");
	pixmap[1][14].load("poker_resource/heartA", "jpg");
	pixmap[1][15].load("poker_resource/heart2", "jpg");

	pixmap[1][3].load("poker_resource/heart3", "jpg");
	pixmap[1][4].load("poker_resource/heart4", "jpg");
	pixmap[1][5].load("poker_resource/heart5", "jpg");
	pixmap[1][6].load("poker_resource/heart6", "jpg");
	pixmap[1][7].load("poker_resource/heart7", "jpg");
	pixmap[1][8].load("poker_resource/heart8", "jpg");
	pixmap[1][9].load("poker_resource/heart9", "jpg");
	pixmap[1][10].load("poker_resource/heart10", "jpg");
	pixmap[1][11].load("poker_resource/heartJ", "jpg");
	pixmap[1][12].load("poker_resource/heartQ", "jpg");
	pixmap[1][13].load("poker_resource/heartK", "jpg");
	pixmap[1][14].load("poker_resource/heartA", "jpg");
	pixmap[1][15].load("poker_resource/heart2", "jpg");


	pixmap[2][3].load("poker_resource/spade3", "jpg");
	pixmap[2][4].load("poker_resource/spade4", "jpg");
	pixmap[2][5].load("poker_resource/spade5", "jpg");
	pixmap[2][6].load("poker_resource/spade6", "jpg");
	pixmap[2][7].load("poker_resource/spade7", "jpg");
	pixmap[2][8].load("poker_resource/spade8", "jpg");
	pixmap[2][9].load("poker_resource/spade9", "jpg");
	pixmap[2][10].load("poker_resource/spade10", "jpg");
	pixmap[2][11].load("poker_resource/spadeJ", "jpg");
	pixmap[2][12].load("poker_resource/spadeQ", "jpg");
	pixmap[2][13].load("poker_resource/spadeK", "jpg");
	pixmap[2][14].load("poker_resource/spadeA", "jpg");
	pixmap[2][15].load("poker_resource/spade2", "jpg");

	pixmap[3][3].load("poker_resource/diamond3", "jpg");
	pixmap[3][4].load("poker_resource/diamond4", "jpg");
	pixmap[3][5].load("poker_resource/diamond5", "jpg");
	pixmap[3][6].load("poker_resource/diamond6", "jpg");
	pixmap[3][7].load("poker_resource/diamond7", "jpg");
	pixmap[3][8].load("poker_resource/diamond8", "jpg");
	pixmap[3][9].load("poker_resource/diamond9", "jpg");
	pixmap[3][10].load("poker_resource/diamond10", "jpg");
	pixmap[3][11].load("poker_resource/diamondJ", "jpg");
	pixmap[3][12].load("poker_resource/diamondQ", "jpg");
	pixmap[3][13].load("poker_resource/diamondK", "jpg");
	pixmap[3][14].load("poker_resource/diamondA", "jpg");
	pixmap[3][15].load("poker_resource/diamond2", "jpg");

}






void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "View Model to Window";

	qreal x = 0.2;
	qreal y = 0.7;

	for (qint32 i = 0; i < *onHandNum;i++)
	{
		qint32 color = onHandCard->cards[i].color;
		qint32 value = onHandCard->cards[i].i;
		addToScene(color, value, x, y, 0.1, 0.15);
		x += 0.03;
	}

	ui.graphicsView->setScene(&scene);
	ui.graphicsView->show();
}

void Window::resizeEvent(QResizeEvent* size)
{
	static qreal preWidth = width();
	static qreal preHeight = height();

	qreal curWidth = width();
	qreal curHeight = height();

	ui.graphicsView->scale(curWidth / preWidth, curHeight / preHeight);

	preWidth = curWidth;
	preHeight = curHeight;
}



void Window::addToScene(int color, int value, qreal rx, qreal ry, qreal rw, qreal rh)
{
	item[color][value].setPixmap(pixmap[color][value].scaled(rw*width(), rh*height()));
	item[color][value].setPos(rx*width(), ry*height());

	scene.addItem(&item[color][value]);
}

void Window::getRatio(int x, int y, qreal &rx, qreal &ry)
{
	rx = (qreal)x / width();
	ry = (qreal)y / height();
}

void Window::moveItem(QGraphicsPixmapItem &item, qreal rx, qreal ry)
{
	item.setPos(rx*width(), ry*height());
}




void Window::buttonClick(void)
{
	qDebug() << "Button Click" << endl;
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
	emit windowCommandSignal(signal);
}

void customScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QTransform transform;
	QGraphicsItem *item;

	QGraphicsScene::mousePressEvent(event);
	//qreal orignal_x = this->itemAt(event->scenePos(), transform)->pos().rx();
	//qreal orignal_y = this->itemAt(event->scenePos(), transform)->pos().ry();
	//this->itemAt(event->scenePos(), transform)->setPos(orignal_x, orignal_y - 30);
	item = this->itemAt(event->scenePos(), transform);
	int indexOfCard = this->items(Qt::AscendingOrder).indexOf(item);
	//item->setPos(event->scenePos().x(), event->scenePos().y() - 30);
	//qreal original_x = (qreal) item->pos().x()+1;
	//qreal original_y = (qreal) item->pos().y()+1;

	//item->setPos(original_x, original_y - 30);
	qDebug() << "index of this item is " << indexOfCard;
}
