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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightLandLordClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;

    void setupUi(QMainWindow *FightLandLordClass)
    {
        if (FightLandLordClass->objectName().isEmpty())
            FightLandLordClass->setObjectName(QStringLiteral("FightLandLordClass"));
        FightLandLordClass->resize(694, 578);
        centralWidget = new QWidget(FightLandLordClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        FightLandLordClass->setCentralWidget(centralWidget);

        retranslateUi(FightLandLordClass);

        QMetaObject::connectSlotsByName(FightLandLordClass);
    } // setupUi

    void retranslateUi(QMainWindow *FightLandLordClass)
    {
        FightLandLordClass->setWindowTitle(QApplication::translate("FightLandLordClass", "FightLandLord", Q_NULLPTR));
        pushButton->setText(QApplication::translate("FightLandLordClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FightLandLordClass: public Ui_FightLandLordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
