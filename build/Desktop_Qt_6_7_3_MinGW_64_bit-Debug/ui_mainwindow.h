/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QWidget *tab_3;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_3;
    QWidget *tab_2;
    QWidget *formLayoutWidget_4;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QLineEdit *lineEdit_10;
    QPushButton *pushButton_4;
    QTableView *tableView;
    QWidget *tab_4;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(952, 677);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(160, 110, 741, 481));
        tab = new QWidget();
        tab->setObjectName("tab");
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 19, 641, 321));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        lineEdit = new QLineEdit(formLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(formLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        lineEdit_3 = new QLineEdit(formLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);

        lineEdit_4 = new QLineEdit(formLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_4);

        pushButton = new QPushButton(formLayoutWidget);
        pushButton->setObjectName("pushButton");

        formLayout->setWidget(4, QFormLayout::FieldRole, pushButton);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        formLayoutWidget_3 = new QWidget(tab_3);
        formLayoutWidget_3->setObjectName("formLayoutWidget_3");
        formLayoutWidget_3->setGeometry(QRect(40, 29, 541, 321));
        formLayout_3 = new QFormLayout(formLayoutWidget_3);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName("formLayout_3");
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(formLayoutWidget_3);
        label_6->setObjectName("label_6");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(formLayoutWidget_3);
        label_7->setObjectName("label_7");

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(formLayoutWidget_3);
        label_8->setObjectName("label_8");

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(formLayoutWidget_3);
        label_9->setObjectName("label_9");

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_9);

        lineEdit_6 = new QLineEdit(formLayoutWidget_3);
        lineEdit_6->setObjectName("lineEdit_6");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, lineEdit_6);

        lineEdit_7 = new QLineEdit(formLayoutWidget_3);
        lineEdit_7->setObjectName("lineEdit_7");

        formLayout_3->setWidget(1, QFormLayout::FieldRole, lineEdit_7);

        lineEdit_8 = new QLineEdit(formLayoutWidget_3);
        lineEdit_8->setObjectName("lineEdit_8");

        formLayout_3->setWidget(2, QFormLayout::FieldRole, lineEdit_8);

        lineEdit_9 = new QLineEdit(formLayoutWidget_3);
        lineEdit_9->setObjectName("lineEdit_9");

        formLayout_3->setWidget(3, QFormLayout::FieldRole, lineEdit_9);

        pushButton_3 = new QPushButton(formLayoutWidget_3);
        pushButton_3->setObjectName("pushButton_3");

        formLayout_3->setWidget(4, QFormLayout::FieldRole, pushButton_3);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        formLayoutWidget_4 = new QWidget(tab_2);
        formLayoutWidget_4->setObjectName("formLayoutWidget_4");
        formLayoutWidget_4->setGeometry(QRect(60, 50, 521, 91));
        formLayout_4 = new QFormLayout(formLayoutWidget_4);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName("formLayout_4");
        formLayout_4->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(formLayoutWidget_4);
        label_10->setObjectName("label_10");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);

        lineEdit_10 = new QLineEdit(formLayoutWidget_4);
        lineEdit_10->setObjectName("lineEdit_10");

        formLayout_4->setWidget(0, QFormLayout::FieldRole, lineEdit_10);

        pushButton_4 = new QPushButton(formLayoutWidget_4);
        pushButton_4->setObjectName("pushButton_4");

        formLayout_4->setWidget(1, QFormLayout::FieldRole, pushButton_4);

        tableView = new QTableView(tab_2);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(60, 171, 521, 211));
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        formLayoutWidget_2 = new QWidget(tab_4);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(30, 69, 561, 71));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget_2);
        label_5->setObjectName("label_5");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        lineEdit_5 = new QLineEdit(formLayoutWidget_2);
        lineEdit_5->setObjectName("lineEdit_5");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_5);

        pushButton_2 = new QPushButton(formLayoutWidget_2);
        pushButton_2->setObjectName("pushButton_2");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, pushButton_2);

        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ID_EMPLOYEE:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "NUM:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "NOM:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "MAIL:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "ID_EMPLOYEE", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "NUM:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "MAIL:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "NOM:", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Entre l'ID:", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Chercher", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Entrez l' ID:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
