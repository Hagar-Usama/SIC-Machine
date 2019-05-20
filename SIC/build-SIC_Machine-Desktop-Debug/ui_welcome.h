/********************************************************************************
** Form generated from reading UI file 'welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionAssemble;
    QAction *actionList_File;
    QAction *actionObject_File;
    QAction *actionLoad_Srcfile;
    QWidget *centralWidget;
    QToolBox *toolBox;
    QWidget *page;
    QPlainTextEdit *src_txt;
    QWidget *page_2;
    QPlainTextEdit *list_txt;
    QWidget *page_3;
    QPlainTextEdit *obj_txt;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAssemble;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QStringLiteral("Welcome"));
        Welcome->setWindowModality(Qt::NonModal);
        Welcome->resize(1729, 1477);
        QFont font;
        font.setPointSize(15);
        Welcome->setFont(font);
        actionLoad = new QAction(Welcome);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionLoad->setFont(font);
        actionSave = new QAction(Welcome);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setFont(font);
        actionSave_as = new QAction(Welcome);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setFont(font);
        actionAssemble = new QAction(Welcome);
        actionAssemble->setObjectName(QStringLiteral("actionAssemble"));
        actionAssemble->setFont(font);
        actionList_File = new QAction(Welcome);
        actionList_File->setObjectName(QStringLiteral("actionList_File"));
        actionList_File->setFont(font);
        actionObject_File = new QAction(Welcome);
        actionObject_File->setObjectName(QStringLiteral("actionObject_File"));
        actionObject_File->setFont(font);
        actionLoad_Srcfile = new QAction(Welcome);
        actionLoad_Srcfile->setObjectName(QStringLiteral("actionLoad_Srcfile"));
        actionLoad_Srcfile->setFont(font);
        centralWidget = new QWidget(Welcome);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        toolBox = new QToolBox(centralWidget);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(30, 50, 1631, 1221));
        QFont font1;
        font1.setPointSize(20);
        toolBox->setFont(font1);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 1631, 1083));
        src_txt = new QPlainTextEdit(page);
        src_txt->setObjectName(QStringLiteral("src_txt"));
        src_txt->setGeometry(QRect(20, 10, 1571, 1061));
        QFont font2;
        font2.setPointSize(25);
        src_txt->setFont(font2);
        toolBox->addItem(page, QStringLiteral("** Source File"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 1631, 1083));
        list_txt = new QPlainTextEdit(page_2);
        list_txt->setObjectName(QStringLiteral("list_txt"));
        list_txt->setGeometry(QRect(10, 0, 1581, 1061));
        list_txt->setFont(font2);
        toolBox->addItem(page_2, QStringLiteral("** List File"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        obj_txt = new QPlainTextEdit(page_3);
        obj_txt->setObjectName(QStringLiteral("obj_txt"));
        obj_txt->setGeometry(QRect(20, 0, 1561, 1061));
        obj_txt->setFont(font2);
        toolBox->addItem(page_3, QStringLiteral("** Object FIle"));
        Welcome->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Welcome);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1729, 43));
        menuBar->setFont(font2);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFile->setFont(font1);
        menuAssemble = new QMenu(menuBar);
        menuAssemble->setObjectName(QStringLiteral("menuAssemble"));
        Welcome->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Welcome);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Welcome->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Welcome);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Welcome->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAssemble->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionLoad_Srcfile);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuAssemble->addAction(actionAssemble);
        menuAssemble->addAction(actionList_File);
        menuAssemble->addAction(actionObject_File);

        retranslateUi(Welcome);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QMainWindow *Welcome)
    {
        Welcome->setWindowTitle(QApplication::translate("Welcome", "SIC Assembler", Q_NULLPTR));
        actionLoad->setText(QApplication::translate("Welcome", "Load", Q_NULLPTR));
        actionSave->setText(QApplication::translate("Welcome", "Save", Q_NULLPTR));
        actionSave_as->setText(QApplication::translate("Welcome", "Save as", Q_NULLPTR));
        actionAssemble->setText(QApplication::translate("Welcome", "Assemble", Q_NULLPTR));
        actionList_File->setText(QApplication::translate("Welcome", "List File", Q_NULLPTR));
        actionObject_File->setText(QApplication::translate("Welcome", "Object File", Q_NULLPTR));
        actionLoad_Srcfile->setText(QApplication::translate("Welcome", "Load Srcfile", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Welcome", "** Source File", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("Welcome", "** List File", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("Welcome", "** Object FIle", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("Welcome", "File", Q_NULLPTR));
        menuAssemble->setTitle(QApplication::translate("Welcome", "Assembler", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
