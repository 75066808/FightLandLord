/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightLandLordClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *btnShowCard;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *FightLandLordClass)
    {
        if (FightLandLordClass->objectName().isEmpty())
            FightLandLordClass->setObjectName(QStringLiteral("FightLandLordClass"));
        FightLandLordClass->resize(1870, 980);
        centralWidget = new QWidget(FightLandLordClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 130, 1261, 791));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        btnShowCard = new QPushButton(centralWidget);
        btnShowCard->setObjectName(QStringLiteral("btnShowCard"));
        btnShowCard->setGeometry(QRect(500, 50, 131, 41));
        FightLandLordClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FightLandLordClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1870, 26));
        FightLandLordClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FightLandLordClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FightLandLordClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FightLandLordClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FightLandLordClass->setStatusBar(statusBar);

        retranslateUi(FightLandLordClass);

        QMetaObject::connectSlotsByName(FightLandLordClass);
    } // setupUi

    void retranslateUi(QMainWindow *FightLandLordClass)
    {
        FightLandLordClass->setWindowTitle(QApplication::translate("FightLandLordClass", "FightLandLord", Q_NULLPTR));
        btnShowCard->setText(QApplication::translate("FightLandLordClass", "Show Card", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FightLandLordClass: public Ui_FightLandLordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
