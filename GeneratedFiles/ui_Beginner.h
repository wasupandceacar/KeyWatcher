/********************************************************************************
** Form generated from reading UI file 'Beginner.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEGINNER_H
#define UI_BEGINNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BeginnerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BeginnerClass)
    {
        if (BeginnerClass->objectName().isEmpty())
            BeginnerClass->setObjectName(QStringLiteral("BeginnerClass"));
        BeginnerClass->resize(600, 400);
        menuBar = new QMenuBar(BeginnerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BeginnerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BeginnerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BeginnerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BeginnerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BeginnerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BeginnerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BeginnerClass->setStatusBar(statusBar);

        retranslateUi(BeginnerClass);

        QMetaObject::connectSlotsByName(BeginnerClass);
    } // setupUi

    void retranslateUi(QMainWindow *BeginnerClass)
    {
        BeginnerClass->setWindowTitle(QApplication::translate("BeginnerClass", "Beginner", 0));
    } // retranslateUi

};

namespace Ui {
    class BeginnerClass: public Ui_BeginnerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEGINNER_H
