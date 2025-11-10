#include "employes.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QItemSelectionModel>
#include <QGridLayout>
#include <QGroupBox>
#include <QDebug>
#include <QDir>
#include <QFormLayout>
#include <QRegularExpressionValidator>

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

    tableView->setModel(employeModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Méthodes de validation
bool MainWindow::validateEmail(const QString &email)
{
    if (email.isEmpty()) return true; // Email optionnel

    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool MainWindow::validatePhone(const QString &phone)
{
    if (phone.isEmpty()) return true; // Téléphone optionnel

    QRegularExpression phoneRegex(R"(^[0-9+\-\s\(\)]{10,15}$)");
    return phoneRegex.match(phone).hasMatch();
}

bool MainWindow::validateName(const QString &name)
{
    if (name.isEmpty()) return false;

    // Autorise les lettres, espaces, apostrophes et traits d'union
    QRegularExpression nameRegex(R"(^[a-zA-ZÀ-ÿ\s\-\']+$)");
    return nameRegex.match(name).hasMatch();
}

bool MainWindow::validateId(const QString &id)
{
    if (id.isEmpty()) return false;

    QRegularExpression idRegex(R"(^\d+$)");
    return idRegex.match(id).hasMatch();
}

void MainWindow::showError(const QString &message)
{
    QMessageBox::warning(this, "Erreur de saisie", message);
}

void MainWindow::highlightErrorField(QLineEdit *field)
{
    field->setStyleSheet("border: 2px solid red; background-color: #ffe6e6;");
}

void MainWindow::clearErrorHighlight(QLineEdit *field)
{
    field->setStyleSheet("");
}

void MainWindow::setupValidators()
{
    // Validateur pour le nom (lettres et caractères spéciaux autorisés)
    QRegularExpression nameRegex(R"(^[a-zA-ZÀ-ÿ\s\-\']*$)");
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);
    lineEdit_2->setValidator(nameValidator);
    lineEdit_7->setValidator(nameValidator);

    // Validateur pour l'email
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-@]*$)");
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(emailRegex, this);
    lineEdit_3->setValidator(emailValidator);
    lineEdit_8->setValidator(emailValidator);

    // Validateur pour le téléphone (chiffres, +, -, espaces, parenthèses)
    QRegularExpression phoneRegex(R"(^[0-9+\-\s\(\)]*$)");
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    lineEdit_4->setValidator(phoneValidator);
    lineEdit_9->setValidator(phoneValidator);

    // Validateur pour les IDs (chiffres seulement)
    QRegularExpression idRegex(R"(^\d*$)");
    QRegularExpressionValidator *idValidator = new QRegularExpressionValidator(idRegex, this);
    lineEdit->setValidator(idValidator);
    lineEdit_5->setValidator(idValidator);
    lineEdit_6->setValidator(idValidator);
    lineEdit_10->setValidator(idValidator);

    // Définir les textes d'aide
    lineEdit_2->setPlaceholderText("Ex: Dupont");
    lineEdit_7->setPlaceholderText("Ex: Dupont");
    lineEdit_3->setPlaceholderText("Ex: exemple@email.com");
    lineEdit_8->setPlaceholderText("Ex: exemple@email.com");
    lineEdit_4->setPlaceholderText("Ex: 0123456789");
    lineEdit_9->setPlaceholderText("Ex: 0123456789");
    lineEdit_5->setPlaceholderText("Entrez l'ID à supprimer");
    lineEdit_6->setPlaceholderText("ID de l'employé à modifier");
    lineEdit_10->setPlaceholderText("ID ou nom à rechercher");
}

void MainWindow::setupUI()
{
    // Utiliser le fichier UI directement
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Créer le tab widget comme dans le fichier UI
    tabWidget = new QTabWidget(centralWidget);
    mainLayout->addWidget(tabWidget);

    // ===== ONGLET AJOUTER =====
    QWidget *tabAjouter = new QWidget();
    tabWidget->addTab(tabAjouter, "Ajouter");

    QWidget *formLayoutWidget = new QWidget(tabAjouter);
    formLayoutWidget->setGeometry(20, 19, 641, 321);

    QFormLayout *formLayout = new QFormLayout(formLayoutWidget);

    // Labels et champs pour l'onglet Ajouter
    QLabel *label = new QLabel("ID_EMPLOYEE:");
    lineEdit = new QLineEdit();
    QLabel *label_3 = new QLabel("NOM:*");
    lineEdit_2 = new QLineEdit();
    QLabel *label_4 = new QLabel("MAIL:");
    lineEdit_3 = new QLineEdit();
    QLabel *label_2 = new QLabel("NUM:");
    lineEdit_4 = new QLineEdit();
    pushButton = new QPushButton("Ajouter");

    formLayout->addRow(label, lineEdit);
    formLayout->addRow(label_3, lineEdit_2);
    formLayout->addRow(label_4, lineEdit_3);
    formLayout->addRow(label_2, lineEdit_4);
    formLayout->addRow(pushButton);

    // ===== ONGLET MODIFIER =====
    QWidget *tabModifier = new QWidget();
    tabWidget->addTab(tabModifier, "Modifier");

    QWidget *formLayoutWidget_3 = new QWidget(tabModifier);
    formLayoutWidget_3->setGeometry(40, 29, 541, 321);

    QFormLayout *formLayout_3 = new QFormLayout(formLayoutWidget_3);

    // Labels et champs pour l'onglet Modifier
    QLabel *label_6 = new QLabel("ID_EMPLOYEE:*");
    lineEdit_6 = new QLineEdit();
    QLabel *label_9 = new QLabel("NOM:*");
    lineEdit_7 = new QLineEdit();
    QLabel *label_8 = new QLabel("MAIL:");
    lineEdit_8 = new QLineEdit();
    QLabel *label_7 = new QLabel("NUM:");
    lineEdit_9 = new QLineEdit();
    pushButton_3 = new QPushButton("Modifier");

    formLayout_3->addRow(label_6, lineEdit_6);
    formLayout_3->addRow(label_9, lineEdit_7);
    formLayout_3->addRow(label_8, lineEdit_8);
    formLayout_3->addRow(label_7, lineEdit_9);
    formLayout_3->addRow(pushButton_3);

    // ===== ONGLET CHERCHER =====
    QWidget *tabChercher = new QWidget();
    tabWidget->addTab(tabChercher, "Chercher");

    QWidget *formLayoutWidget_4 = new QWidget(tabChercher);
    formLayoutWidget_4->setGeometry(60, 50, 521, 99);

    QFormLayout *formLayout_4 = new QFormLayout(formLayoutWidget_4);

    QLabel *label_10 = new QLabel("Entre l'ID ou le nom:");
    lineEdit_10 = new QLineEdit();
    pushButton_4 = new QPushButton("Chercher");

    formLayout_4->addRow(label_10, lineEdit_10);
    formLayout_4->addRow(pushButton_4);

    // Table view pour l'onglet Chercher
    tableView = new QTableView(tabChercher);
    tableView->setGeometry(60, 171, 521, 211);

    // ===== ONGLET SUPPRIMER =====
    QWidget *tabSupprimer = new QWidget();
    tabWidget->addTab(tabSupprimer, "Supprimer");

    QWidget *formLayoutWidget_2 = new QWidget(tabSupprimer);
    formLayoutWidget_2->setGeometry(30, 69, 561, 99);

    QFormLayout *formLayout_2 = new QFormLayout(formLayoutWidget_2);

    QLabel *label_5 = new QLabel("Entrez l'ID:*");
    lineEdit_5 = new QLineEdit();
    pushButton_2 = new QPushButton("supprimer");

    formLayout_2->addRow(label_5, lineEdit_5);
    formLayout_2->addRow(pushButton_2);

    // Configurer les validateurs
    setupValidators();

    // Appliquer le styleSheet du fichier UI
    QString styleSheet = R"(
/* Thème Rose/Saumon créatif pour l'interface d'événements */

/* Style général de la fenêtre */
QWidget {
    background-color: #fff0f5; /* Rose lavande très clair */
    color: #8b475d; /* Rose foncé */
    font-family: 'Segoe UI', Arial, sans-serif;
    font-size: 14px;
}

/* ===== STYLE DES ONGLETS (TAB WIDGET) ===== */
QTabWidget::pane {
    border: 3px solid #ffb6c1;
    border-radius: 12px;
    background: rgba(255, 255, 255, 0.9);
    margin: 5px;
}

QTabWidget::tab-bar {
    alignment: center;
}

QTabBar::tab {
    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                stop: 0 #ffe4e9, stop: 0.4 #ffd1dc, stop: 1 #ffb6c1);
    border: 2px solid #ff91a4;
    border-bottom: none;
    border-top-left-radius: 8px;
    border-top-right-radius: 8px;
    min-width: 90px;
    padding: 10px 15px;
    margin-right: 2px;
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    font-size: 12px;
    font-weight: bold;
    color: #8b475d;
}

QTabBar::tab:selected {
    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                stop: 0 #ffffff, stop: 1 #ffd1dc);
    border: 2px solid #ff6b8b;
    font-weight: bolder;
}

QTabBar::tab:hover {
    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                stop: 0 #ffffff, stop: 1 #ff91a4);
}

/* Style des boutons principaux */
QPushButton {
    background-color: #ffd1dc; /* Rose pastel */
    color: #8b475d;
    border: 2px solid #ffb6c1;
    border-radius: 15px;
    padding: 10px 20px;
    font-weight: bold;
    margin: 3px;
    font-size: 14px;
}

QPushButton:hover {
    background-color: #ffb6c1;
    border: 2px solid #ff91a4;
}

QPushButton:pressed {
    background-color: #ff91a4;
}

/* Style spécifique pour chaque bouton avec des couleurs différentes */
QPushButton[text="Ajouter"] {
    background-color: #ffd1dc; /* Rose clair */
    border: 2px solid #ffb6c1;
    color: #8b475d;
}

QPushButton[text="Afficher"] {
    background-color: #ffcccb; /* Saumon clair */
    border: 2px solid #ffa07a;
    color: #8b475d;
}

QPushButton[text="Modifier"] {
    background-color: #f8c8dc; /* Rose poudré */
    border: 2px solid #f4acb6;
    color: #8b475d;
}

QPushButton[text="Supprimer"] {
    background-color: #ffb7c5; /* Rose corail */
    border: 2px solid #ff91a4;
    color: #8b475d;
}

/* Style des champs de saisie */
QLineEdit {
    background-color: #ffffff;
    border: 2px solid #ffd1dc;
    border-radius: 10px;
    padding: 8px 12px;
    color: #8b475d;
    font-size: 14px;
}

QLineEdit:focus {
    border: 2px solid #ff91a4;
    background-color: #fffafafa;
}

/* Style des labels */
QLabel {
    color: #8b475d;
    font-weight: bold;
    padding: 5px;
    background-color: rgba(255, 240, 245, 0.7); /* Fond rose très léger */
    border-radius: 8px;
    font-size: 14px;
}

/* Style du titre "Ajouter un evenement" */
QLabel[text="Ajouter un evenement"] {
    font-size: 18px;
    font-weight: bold;
    color: #8b475d;
    background-color: rgba(255, 209, 220, 0.8);
    padding: 10px;
    border-radius: 12px;
    text-align: center;
}

/* Style du bouton "ajouter" en bas */
QPushButton[text="ajouter"] {
    background-color: #ffb6c1; /* Rose moyen */
    border: 2px solid #ff91a4;
    color: #8b475d;
    border-radius: 20px;
    padding: 12px 25px;
    font-size: 16px;
    font-weight: bold;
}

QPushButton[text="ajouter"]:hover {
    background-color: #ff91a4;
}

/* Style pour les champs numériques */
QLineEdit[placeholderText="0"] {
    background-color: #fffaf0;
    border: 2px solid #ffebcd;
}

/* Style pour le champ date */
QLineEdit[text="1/1/2000"] {
    background-color: #fff0f5;
    border: 2px solid #ffd1dc;
}

/* Style pour les QTextEdit dans les table widgets */
QTextEdit {
    background-color: #ffffff;
    border: 2px solid #ffd1dc;
    border-radius: 8px;
    padding: 6px 10px;
    color: #8b475d;
    font-size: 14px;
    selection-background-color: #ffb6c1;
}

QTextEdit:focus {
    border: 2px solid #ff91a4;
    background-color: #fffafafa;
}

/* Style pour les QTableWidget */
QTableWidget {
    background-color: #ffffff;
    border: 2px solid #ffd1dc;
    border-radius: 8px;
    gridline-color: #ffd1dc;
    font-size: 14px;
}

QTableWidget::item {
    padding: 6px;
    border-bottom: 1px solid #ffe4e9;
    color: #8b475d;
}

QTableWidget::item:selected {
    background-color: #ffb6c1;
    color: #8b475d;
}

QHeaderView::section {
    background-color: #ffd1dc;
    color: #8b475d;
    padding: 8px;
    border: 1px solid #ffb6c1;
    font-weight: bold;
    font-size: 14px;
}

/* Effets d'ombre légers pour la profondeur */
QPushButton, QLineEdit, QLabel, QTextEdit, QTableWidget {
    border-radius: 10px;
}

/* Style pour le layout général */
QWidget#centralWidget {
    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,
                                stop: 0 #fff0f5, stop: 1 #ffe4e9);
    border-radius: 15px;
}

/* Style pour les cases à cocher */
QCheckBox {
    color: #8b475d;
    font-size: 14px;
    spacing: 6px;
}

QCheckBox::indicator {
    width: 16px;
    height: 16px;
    border: 2px solid #ffb6c1;
    border-radius: 4px;
    background: white;
}

QCheckBox::indicator:checked {
    background: #ff91a4;
    border: 2px solid #ff6b8b;
}

/* Style pour les champs obligatoires */
QLabel[text*="*"] {
    color: #ff4444;
    font-weight: bold;
}

/* Style pour les champs en erreur */
QLineEdit[style*="red"] {
    border: 2px solid red;
    background-color: #ffe6e6;
}
)";

    centralWidget->setStyleSheet(styleSheet);

    // Connecter les signaux
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::on_ajouterBtn_clicked);
    connect(pushButton_3, &QPushButton::clicked, this, &MainWindow::on_modifierBtn_clicked);
    connect(pushButton_2, &QPushButton::clicked, this, &MainWindow::on_supprimerBtn_clicked);
    connect(pushButton_4, &QPushButton::clicked, this, &MainWindow::on_chercherBtn_clicked);
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::on_employeTable_selectionChanged);
}

void MainWindow::on_ajouterBtn_clicked()
{
    // Réinitialiser les surlignages d'erreur
    clearErrorHighlight(lineEdit_2);
    clearErrorHighlight(lineEdit_3);
    clearErrorHighlight(lineEdit_4);

    // Validation du nom (obligatoire)
    if (lineEdit_2->text().isEmpty()) {
        showError("Le nom est obligatoire!");
        highlightErrorField(lineEdit_2);
        return;
    }

    if (!validateName(lineEdit_2->text())) {
        showError("Le nom ne doit contenir que des lettres, espaces, apostrophes et traits d'union!");
        highlightErrorField(lineEdit_2);
        return;
    }

    // Validation de l'email (optionnel mais doit être valide si renseigné)
    if (!lineEdit_3->text().isEmpty() && !validateEmail(lineEdit_3->text())) {
        showError("L'adresse email n'est pas valide!\nExemple: exemple@email.com");
        highlightErrorField(lineEdit_3);
        return;
    }

    // Validation du téléphone (optionnel mais doit être valide si renseigné)
    if (!lineEdit_4->text().isEmpty() && !validatePhone(lineEdit_4->text())) {
        showError("Le numéro de téléphone n'est pas valide!\nDoit contenir 10 à 15 chiffres.");
        highlightErrorField(lineEdit_4);
        return;
    }

    QSqlQuery query;
    QString sql = QString("INSERT INTO employe (nom, mail, num) VALUES ('%1', '%2', '%3')")
                      .arg(lineEdit_2->text())
                      .arg(lineEdit_3->text())
                      .arg(lineEdit_4->text());
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
    // Réinitialiser les surlignages d'erreur
    clearErrorHighlight(lineEdit_6);
    clearErrorHighlight(lineEdit_7);
    clearErrorHighlight(lineEdit_8);
    clearErrorHighlight(lineEdit_9);

    // Validation de l'ID
    if (lineEdit_6->text().isEmpty()) {
        showError("L'ID est obligatoire pour la modification!");
        highlightErrorField(lineEdit_6);
        return;
    }

    if (!validateId(lineEdit_6->text())) {
        showError("L'ID doit être un nombre valide!");
        highlightErrorField(lineEdit_6);
        return;
    }

    // Validation du nom
    if (lineEdit_7->text().isEmpty()) {
        showError("Le nom est obligatoire!");
        highlightErrorField(lineEdit_7);
        return;
    }

    if (!validateName(lineEdit_7->text())) {
        showError("Le nom ne doit contenir que des lettres, espaces, apostrophes et traits d'union!");
        highlightErrorField(lineEdit_7);
        return;
    }

    // Validation de l'email
    if (!lineEdit_8->text().isEmpty() && !validateEmail(lineEdit_8->text())) {
        showError("L'adresse email n'est pas valide!\nExemple: exemple@email.com");
        highlightErrorField(lineEdit_8);
        return;
    }

    // Validation du téléphone
    if (!lineEdit_9->text().isEmpty() && !validatePhone(lineEdit_9->text())) {
        showError("Le numéro de téléphone n'est pas valide!\nDoit contenir 10 à 15 chiffres.");
        highlightErrorField(lineEdit_9);
        return;
    }

    int employeId = lineEdit_6->text().toInt();

    // Vérifier si l'employé existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id_employe FROM employe WHERE id_employe = ?");
    checkQuery.addBindValue(employeId);
    if (!checkQuery.exec() || !checkQuery.next()) {
        showError("Aucun employé trouvé avec cet ID!");
        highlightErrorField(lineEdit_6);
        return;
    }

    QSqlQuery query;
    QString sql = QString("UPDATE employe SET nom='%1', mail='%2', num='%3' WHERE id_employe=%4")
                      .arg(lineEdit_7->text())
                      .arg(lineEdit_8->text())
                      .arg(lineEdit_9->text())
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
    // Réinitialiser le surlignage d'erreur
    clearErrorHighlight(lineEdit_5);

    // Validation de l'ID
    if (lineEdit_5->text().isEmpty()) {
        showError("L'ID est obligatoire pour la suppression!");
        highlightErrorField(lineEdit_5);
        return;
    }

    if (!validateId(lineEdit_5->text())) {
        showError("L'ID doit être un nombre valide!");
        highlightErrorField(lineEdit_5);
        return;
    }

    int employeId = lineEdit_5->text().toInt();

    // Vérifier si l'employé existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT nom FROM employe WHERE id_employe = ?");
    checkQuery.addBindValue(employeId);
    if (!checkQuery.exec() || !checkQuery.next()) {
        showError("Aucun employé trouvé avec cet ID!");
        highlightErrorField(lineEdit_5);
        return;
    }

    QString employeName = checkQuery.value(0).toString();

    // Demander confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  QString("Êtes-vous sûr de vouloir supprimer l'employé '%1' (ID: %2) ?")
                                      .arg(employeName).arg(employeId),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

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
    QString searchText = lineEdit_10->text().trimmed();

    if (searchText.isEmpty()) {
        // Si le champ est vide, afficher tous les employés
        if (db.isOpen()) {
            QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
            if (model) {
                model->setFilter("");
                model->select();
            }
        }
        return;
    }

    if (db.isOpen()) {
        QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
        if (model) {
            QString filter;
            if (validateId(searchText)) {
                // Recherche par ID
                filter = QString("id_employe = %1").arg(searchText.toInt());
            } else {
                // Recherche par nom
                filter = QString("nom LIKE '%%1%'").arg(searchText);
            }
            model->setFilter(filter);
            model->select();

            // Vérifier si des résultats ont été trouvés
            if (model->rowCount() == 0) {
                QMessageBox::information(this, "Recherche", "Aucun employé trouvé avec ces critères.");
            }
        }
    }
}

void MainWindow::on_employeTable_selectionChanged()
{
    QModelIndex currentIndex = tableView->currentIndex();
    if (!currentIndex.isValid())
        return;
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
    if (model) {
        QSqlRecord record = model->record(currentIndex.row());
        // Mettre à jour les champs de l'onglet Modifier
        lineEdit_6->setText(record.value("id_employe").toString());
        lineEdit_7->setText(record.value("nom").toString());
        lineEdit_8->setText(record.value("mail").toString());
        lineEdit_9->setText(record.value("num").toString());

        // Mettre à jour les champs de l'onglet Supprimer
        lineEdit_5->setText(record.value("id_employe").toString());

        // Mettre à jour les champs de l'onglet Chercher
        lineEdit_10->setText(record.value("id_employe").toString());

        // Réinitialiser les surlignages d'erreur
        clearErrorHighlight(lineEdit_6);
        clearErrorHighlight(lineEdit_7);
        clearErrorHighlight(lineEdit_8);
        clearErrorHighlight(lineEdit_9);
        clearErrorHighlight(lineEdit_5);
    }
}

void MainWindow::clearForm()
{
    lineEdit->clear();
    lineEdit_2->clear();
    lineEdit_3->clear();
    lineEdit_4->clear();

    // Réinitialiser les surlignages d'erreur
    clearErrorHighlight(lineEdit_2);
    clearErrorHighlight(lineEdit_3);
    clearErrorHighlight(lineEdit_4);
}

int MainWindow::getSelectedEmployeId()
{
    QModelIndex currentIndex = tableView->currentIndex();
    if (!currentIndex.isValid())
        return -1;
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
    if (model) {
        QSqlRecord record = model->record(currentIndex.row());
        return record.value("id_employe").toInt();
    }
    return -1;
}
