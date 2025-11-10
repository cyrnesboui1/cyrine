#ifndef EMPLOYES_H
#define EMPLOYES_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTabWidget>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterBtn_clicked();
    void on_modifierBtn_clicked();
    void on_supprimerBtn_clicked();
    void on_chercherBtn_clicked();
    void on_employeTable_selectionChanged();

private:
    // Widgets pour l'onglet Ajouter
    QLineEdit *lineEdit;      // ID_EMPLOYEE
    QLineEdit *lineEdit_2;    // NOM
    QLineEdit *lineEdit_3;    // MAIL
    QLineEdit *lineEdit_4;    // NUM
    QPushButton *pushButton;  // Bouton Ajouter

    // Widgets pour l'onglet Modifier
    QLineEdit *lineEdit_6;    // ID_EMPLOYEE
    QLineEdit *lineEdit_7;    // NOM
    QLineEdit *lineEdit_8;    // MAIL
    QLineEdit *lineEdit_9;    // NUM
    QPushButton *pushButton_3; // Bouton Modifier

    // Widgets pour l'onglet Chercher
    QLineEdit *lineEdit_10;   // ID
    QPushButton *pushButton_4; // Bouton Chercher
    QTableView *tableView;    // Table view

    // Widgets pour l'onglet Supprimer
    QLineEdit *lineEdit_5;    // ID
    QPushButton *pushButton_2; // Bouton Supprimer

    QTabWidget *tabWidget;
    QSqlDatabase db;

    void connectToDatabase();
    void setupDatabaseModels();
    void setupUI();
    void clearForm();
    int getSelectedEmployeId();

    // Nouvelles méthodes de contrôle de saisie
    bool validateEmail(const QString &email);
    bool validatePhone(const QString &phone);
    bool validateName(const QString &name);
    bool validateId(const QString &id);
    void setupValidators();
    void showError(const QString &message);
    void highlightErrorField(QLineEdit *field);
    void clearErrorHighlight(QLineEdit *field);
};

#endif // EMPLOYES_H
