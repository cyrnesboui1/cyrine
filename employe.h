#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouterBtn_clicked();
    void on_modifierBtn_clicked();
    void on_supprimerBtn_clicked();
    void on_chercherBtn_clicked();
    void on_employeTable_selectionChanged();

private:
    void connectToDatabase();
    void setupDatabaseModels();
    void setupUI();
    void clearForm();
    int getSelectedEmployeId();

    QSqlDatabase db;
    QWidget *central;
    QTableView *employeTable;
    QPushButton *ajouterBtn;
    QPushButton *modifierBtn;
    QPushButton *chercherBtn;
    QPushButton *supprimerBtn;
    QLineEdit *idEdit;
    QLineEdit *nomEdit;
    QLineEdit *mailEdit;
    QLineEdit *numEdit;
};

#endif // EMPLOYE_H
