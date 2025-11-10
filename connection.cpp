#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    // Nom du DSN créé dans ODBC
    db.setDatabaseName("projet2A");

    // Identifiants Oracle
    db.setUserName("cyrinesboui");
    db.setPassword("cyrine123");

    if (!db.open()) {
        qDebug() << "Erreur connexion DB:" << db.lastError().text();
        return false;
    }

    qDebug() << " Connexion Oracle réussie via ODBC !";
    return true;
}
