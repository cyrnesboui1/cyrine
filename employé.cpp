void MainWindow::on_ajouterBtn_clicked()
{
    if (nomEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom est obligatoire!");
        return;
    }

    if (!db.isOpen()) {
        QMessageBox::warning(this, "Erreur", "Base de données non connectée!");
        return;
    }

    // MÉTHODE SIMPLE SANS PARAMÈTRES
    QSqlQuery query;
    QString sql = QString("INSERT INTO employe (nom, mail, num) VALUES ('%1', '%2', '%3')")
                      .arg(nomEdit->text())
                      .arg(mailEdit->text())
                      .arg(numEdit->text());

    qDebug() << "SQL d'insertion:" << sql;

    if (!query.exec(sql)) {
        QMessageBox::warning(this, "Erreur",
                             "Erreur lors de l'ajout: " + query.lastError().text() +
                                 "\nSQL: " + sql);
    } else {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès!");
        setupDatabaseModels();
        clearForm();
    }
}

void MainWindow::on_modifierBtn_clicked()
{
    int employeId = -1;

    if (!idEdit->text().isEmpty()) {
        employeId = idEdit->text().toInt();
    } else {
        employeId = getSelectedEmployeId();
    }

    if (employeId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé ou saisir un ID!");
        return;
    }

    if (nomEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom est obligatoire!");
        return;
    }

    QSqlQuery query;
    QString sql = QString("UPDATE employe SET nom = '%1', mail = '%2', num = '%3' WHERE id_employe = %4")
                      .arg(nomEdit->text())
                      .arg(mailEdit->text())
                      .arg(numEdit->text())
                      .arg(employeId);

    if (!query.exec(sql)) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la modification: " + query.lastError().text());
    } else {
        setupDatabaseModels();
        QMessageBox::information(this, "Succès", "Employé modifié avec succès!");
    }
}

void MainWindow::on_supprimerBtn_clicked()
{
    int employeId = -1;

    if (!idEdit->text().isEmpty()) {
        employeId = idEdit->text().toInt();
    } else {
        employeId = getSelectedEmployeId();
    }

    if (employeId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé ou saisir un ID!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet employé?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        QString sql = QString("DELETE FROM employe WHERE id_employe = %1").arg(employeId);

        if (!query.exec(sql)) {
            QMessageBox::warning(this, "Erreur", "Erreur lors de la suppression: " + query.lastError().text());
        } else {
            QMessageBox::information(this, "Succès", "Employé supprimé avec succès!");
            setupDatabaseModels();
            clearForm();
        }
    }
}

void MainWindow::on_chercherBtn_clicked()
{
    QString searchText = idEdit->text();

    if (db.isOpen()) {
        QSqlTableModel *model = qobject_cast<QSqlTableModel*>(employeTable->model());
        if (model) {
            if (searchText.isEmpty()) {
                model->setFilter("");
            } else {
                QString filter = QString("id_employe = %1 OR nom LIKE '%%2%' OR mail LIKE '%%2%' OR num LIKE '%%2%'")
                .arg(searchText.toInt()).arg(searchText);
                model->setFilter(filter);
            }
            model->select();

            if (model->rowCount() == 1) {
                QSqlRecord record = model->record(0);
                idEdit->setText(record.value("id_employe").toString());
                nomEdit->setText(record.value("nom").toString());
                mailEdit->setText(record.value("mail").toString());
                numEdit->setText(record.value("num").toString());
            }
        }
    }
}
