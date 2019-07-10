#include "window.h"


Window::Window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btnShowCard, SIGNAL(clicked()), this, SLOT(buttonClick()));
}

void Window::setCurrentCardsInHand(const qint8* cards)
{
	currentCardsInHand = cards;
}


void Window::windowNotificationSlot(std::shared_ptr<Signal> signal)
{
	qDebug() << "View Model to Window";
	QPixmap *cardTempPixmap = new QPixmap();

	QGraphicsScene *Scene = new QGraphicsScene();

	qreal init_x = 10;
	qreal init_y = 10;

	//int cardNum = 15;

	size_t cardCnt = 0;

	Scene->setSceneRect(300, -100, 1, 1);

	for (size_t i = 3; i < 18; i++)
	{
		if (currentCardsInHand[i] == 0)
			continue;
		else
		{
			switch (i)
			{
			case 3:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club3", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 4:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club4", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 5:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club5", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 6:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club6", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 7:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club7", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 8:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club8", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 9:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club9", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 10:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club10", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 11:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubJ", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 12:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubQ", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 13:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubK", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 14:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/clubA", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 15:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/club2", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 16:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/joker1", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			case 17:
				cardCnt += currentCardsInHand[i];
				for (size_t j = 0; j < currentCardsInHand[i]; j++)
				{
					cardTempPixmap->load("poker_resource/joker2", "jpg");
					addCardInScene(init_x + (cardCnt - 1) * 20, init_y, cardTempPixmap, Scene);
				}
				break;
			default:
				break;
			}
		}		
	}


	//addCardInScene(init_x + i*20, init_y, cardTempPixmap, Scene);


	ui.graphicsView->setScene(Scene);

	ui.graphicsView->show();
	
}

void Window::addCardInScene(qreal x, qreal y, QPixmap* cardTempPixmap, QGraphicsScene* Scene)
{
	//cardTempPixmap->load("poker_resource/joker1", "jpg");
	Scene->addPixmap(*cardTempPixmap)->setPos(x, y);

}

void Window::buttonClick(void)
{
	qDebug() << "Button Click" << endl;
	std::shared_ptr<Signal> signal = std::make_shared<Signal>();

	signal->signalType = CONNECT;
	emit windowCommandSignal(signal);
}
