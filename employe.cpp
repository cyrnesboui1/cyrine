#include "employe.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QItemSelectionModel>
#include <QGridLayout>
#include <QGroupBox>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();
    connectToDatabase();
    if (db.isOpen()) {
        setupDatabaseModels();
    }
}

MainWindow::~MainWindow()
{
    if (db.isOpen()) {
        db.close();
    }
}

void MainWindow::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QDir::currentPath() + "/gestion_employes.db";
    db.setDatabaseName(dbPath);
    qDebug() << "Chemin de la base de données:" << dbPath;

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la base de données: " + db.lastError().text());
        return;
    }

    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS employe");
    QString createSQL = "CREATE TABLE employe ("
                        "id_employe INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "nom TEXT NOT NULL, "
                        "mail TEXT, "
                        "num TEXT)";
    if (!query.exec(createSQL)) {
        QMessageBox::critical(this, "Erreur", "Erreur création table: " + query.lastError().text());
        return;
    }

    qDebug() << "Table 'employe' créée avec succès";
    query.exec("INSERT INTO employe (nom, mail, num) VALUES ('Dupont', 'pierre.dupont@email.com', '0123456789')");
    query.exec("INSERT INTO employe (nom, mail, num) VALUES ('Martin', 'sophie.martin@email.com', '0987654321')");
    query.exec("INSERT INTO employe (nom, mail, num) VALUES ('Bernard', 'luc.bernard@email.com', '0654321987')");

    QMessageBox::information(this, "Succès", "Connexion réussite !\nBase de données créée: gestion_employes.db");
}

void MainWindow::setupDatabaseModels()
{
    if (!db.isOpen()) {
        QMessageBox::warning(this, "Erreur", "Base de données non connectée!");
        return;
    }

    QSqlTableModel *employeModel = new QSqlTableModel(this, db);
    employeModel->setTable("employe");
    employeModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    employeModel->setHeaderData(0, Qt::Horizontal, "ID");
    employeModel->setHeaderData(1, Qt::Horizontal, "NOM");
    employeModel->setHeaderData(2, Qt::Horizontal, "MAIL");
    employeModel->setHeaderData(3, Qt::Horizontal, "NUM");

    if (!employeModel->select()) {
        QMessageBox::warning(this, "Erreur", "Erreur chargement employés: " + employeModel->lastError().text());
        return;
    }

    employeTable->setModel(employeModel);
    employeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setupUI()
{
    central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    QVBoxLayout *menuLayout = new QVBoxLayout();
    ajouterBtn = new QPushButton("Ajouter");
    modifierBtn = new QPushButton("Modifier");
    chercherBtn = new QPushButton("Chercher");
    supprimerBtn = new QPushButton("Supprimer");
    menuLayout->addWidget(ajouterBtn);
    menuLayout->addWidget(modifierBtn);
    menuLayout->addWidget(chercherBtn);
    menuLayout->addWidget(supprimerBtn);
    menuLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout();
    QLabel *titleLabel = new QLabel("Ajouter");
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    rightLayout->addWidget(titleLabel);

    QGroupBox *idGroup = new QGroupBox("ID_EMPLOYEE:");
    QVBoxLayout *idLayout = new QVBoxLayout(idGroup);
    QGridLayout *formLayout = new QGridLayout();
    formLayout->addWidget(new QLabel("ID:"), 0, 0);
    idEdit = new QLineEdit();
    idEdit->setPlaceholderText("Pour recherche/modification");
    formLayout->addWidget(idEdit, 0, 1);
    formLayout->addWidget(new QLabel("NOM:"), 1, 0);
    nomEdit = new QLineEdit();
    formLayout->addWidget(nomEdit, 1, 1);
    formLayout->addWidget(new QLabel("MAIL:"), 2, 0);
    mailEdit = new QLineEdit();
    formLayout->addWidget(mailEdit, 2, 1);
    formLayout->addWidget(new QLabel("NUM:"), 3, 0);
    numEdit = new QLineEdit();
    formLayout->addWidget(numEdit, 3, 1);
    idLayout->addLayout(formLayout);
    rightLayout->addWidget(idGroup);

    employeTable = new QTableView();
    employeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    rightLayout->addWidget(employeTable);

    mainLayout->addLayout(menuLayout, 1);
    mainLayout->addLayout(rightLayout, 4);

    connect(ajouterBtn, &QPushButton::clicked, this, &MainWindow::on_ajouterBtn_clicked);
    connect(modifierBtn, &QPushButton::clicked, this, &MainWindow::on_modifierBtn_clicked);
    connect(supprimerBtn, &QPushButton::clicked, this, &MainWindow::on_supprimerBtn_clicked);
    connect(chercherBtn, &QPushButton::clicked, this, &MainWindow::on_chercherBtn_clicked);
}

void MainWindow::on_ajouterBtn_clicked()
{
    if (nomEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom est obligatoire!");
        return;
    }

    QSqlQuery query;
    QString sql = QString("INSERT INTO employe (nom, mail, num) VALUES ('%1', '%2', '%3')")
                      .arg(nomEdit->text())
                      .arg(mailEdit->text())
                      .arg(numEdit->text());
    if (!query.exec(sql)) {
        QMessageBox::warning(this, "Erreur", "Erreur ajout: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès!");
        setupDatabaseModels();
        clearForm();
    }
}

void MainWindow::on_modifierBtn_clicked()
{
    int employeId = idEdit->text().toInt();
    QSqlQuery query;
    QString sql = QString("UPDATE employe SET nom='%1', mail='%2', num='%3' WHERE id_employe=%4")
                      .arg(nomEdit->text())
                      .arg(mailEdit->text())
                      .arg(numEdit->text())
                      .arg(employeId);
    if (!query.exec(sql)) {
        QMessageBox::warning(this, "Erreur", "Erreur modification: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Employé modifié !");
        setupDatabaseModels();
    }
}

void MainWindow::on_supprimerBtn_clicked()
{
    int employeId = idEdit->text().toInt();
    QSqlQuery query;
    QString sql = QString("DELETE FROM employe WHERE id_employe=%1").arg(employeId);
    if (!query.exec(sql)) {
        QMessageBox::warning(this, "Erreur", "Erreur suppression: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Employé supprimé !");
        setupDatabaseModels();
        clearForm();
    }
}

void MainWindow::on_chercherBtn_clicked()
{
    QString searchText = idEdit->text();
    if (db.isOpen()) {
        QSqlTableModel *model = qobject_cast<QSqlTableModel *>(employeTable->model());
        if (model) {
            if (searchText.isEmpty()) {
                model->setFilter("");
            } else {
                QString filter = QString("id_employe = %1 OR nom LIKE '%%2%'").arg(searchText.toInt()).arg(searchText);
                model->setFilter(filter);
            }
            model->select();
        }
    }
}

void MainWindow::on_employeTable_selectionChanged()
{
    QModelIndex currentIndex = employeTable->currentIndex();
    if (!currentIndex.isValid())
        return;
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(employeTable->model());
    if (model) {
        QSqlRecord record = model->record(currentIndex.row());
        idEdit->setText(record.value("id_employe").toString());
        nomEdit->setText(record.value("nom").toString());
        mailEdit->setText(record.value("mail").toString());
        numEdit->setText(record.value("num").toString());
    }
}

void MainWindow::clearForm()
{
    idEdit->clear();
    nomEdit->clear();
    mailEdit->clear();
    numEdit->clear();
}

int MainWindow::getSelectedEmployeId()
{
    QModelIndex currentIndex = employeTable->currentIndex();
    if (!currentIndex.isValid())
        return -1;
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(employeTable->model());
    if (model) {
        QSqlRecord record = model->record(currentIndex.row());
        return record.value("id_employe").toInt();
    }
    return -1;
}
