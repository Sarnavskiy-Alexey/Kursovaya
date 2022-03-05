#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<T_aviation> vector_T_aviation;
QVector<T_enemy> vector_T_enemy;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Database */

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("../Kurs/kursovaya.db");

    if (!m_db.open())
    {
        QString error = "Error: can't connect to db!";
        qDebug() << "Error: can't connect to db!";
        ui->statusbar->showMessage(error);
    }
    else
    {
        QString success = "Success: connection is good!";
        qDebug() << "Success: connection is good!";
        ui->statusbar->showMessage(success);
    }

    /* *********** */
    printAllAircrafts_T_aviation();
    printAllEnemies_T_enemy();
}

MainWindow::~MainWindow()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }

    delete ui;
}


/* ****************************************************** */


void MainWindow::on_pushButton_exit_clicked()
{
    exit(0);
}


void MainWindow::on_listWidget_availableACK_itemSelectionChanged()
{
    int i;
    for (i = 0; i < vector_T_aviation.size(); i++)
    {
        if (i == ui->listWidget_availableACK->currentRow())
        {
            ui->lineEdit_name->setText(vector_T_aviation[i].name);
            ui->lineEdit_country->setText(vector_T_aviation[i].country);
            ui->lineEdit_wingspan->setText(vector_T_aviation[i].wingspan);
            ui->lineEdit_mass->setText(vector_T_aviation[i].mass);
            ui->lineEdit_velocity->setText(vector_T_aviation[i].velocity);
            ui->lineEdit_armamentUnits->setText(vector_T_aviation[i].armament_units);
            ui->lineEdit_combatRadius->setText(vector_T_aviation[i].combat_radius);
            ui->lineEdit_flightRange->setText(vector_T_aviation[i].flight_range);
            ui->lineEdit_cost->setText(vector_T_aviation[i].cost);

            break;
        }
    }
}


void MainWindow::on_pushButton_clearACK_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_country->clear();
    ui->lineEdit_wingspan->clear();
    ui->lineEdit_mass->clear();
    ui->lineEdit_velocity->clear();
    ui->lineEdit_armamentUnits->clear();
    ui->lineEdit_combatRadius->clear();
    ui->lineEdit_flightRange->clear();
    ui->lineEdit_cost->clear();
}


void MainWindow::on_pushButton_addACK_clicked()
{
    if (ui->lineEdit_name->text().isEmpty())
    {
        ui->statusbar->showMessage("Название не заполнено!");
    }
    else if (ui->lineEdit_country->text().isEmpty())
    {
        ui->statusbar->showMessage("Страна не заполнена");
    }
    else if (ui->lineEdit_wingspan->text().isEmpty())
    {
        ui->statusbar->showMessage("Размах крыла не заполнен");
    }
    else if (ui->lineEdit_mass->text().isEmpty())
    {
        ui->statusbar->showMessage("Масса пустого не заполнена");
    }
    else if (ui->lineEdit_velocity->text().isEmpty())
    {
        ui->statusbar->showMessage("Скорость полета не заполнена");
    }
    else if (ui->lineEdit_armamentUnits->text().isEmpty())
    {
        ui->statusbar->showMessage("Узлы вооружения не заполнены");
    }
    else if (ui->lineEdit_combatRadius->text().isEmpty())
    {
        ui->statusbar->showMessage("Боевой радиус не заполнен");
    }
    else if (ui->lineEdit_flightRange->text().isEmpty())
    {
        ui->statusbar->showMessage("Дальность полета не заполнена");
    }
    else if (ui->lineEdit_cost->text().isEmpty())
    {
        ui->statusbar->showMessage("Стоимость не заполнена");
    }
    else
    {
        if (checkAircrafts_T_aviation())
        {
            ui->statusbar->clearMessage();

            QSqlQuery queryAdd;
            queryAdd.prepare(
                        QString("INSERT INTO aviation (name, country, wingspan, mass, velocity, armament_units, combat_radius, flight_range, cost) VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9');")
                        .arg(ui->lineEdit_name->text())
                        .arg(ui->lineEdit_country->text())
                        .arg(ui->lineEdit_wingspan->text())
                        .arg(ui->lineEdit_mass->text())
                        .arg(ui->lineEdit_velocity->text())
                        .arg(ui->lineEdit_armamentUnits->text())
                        .arg(ui->lineEdit_combatRadius->text())
                        .arg(ui->lineEdit_flightRange->text())
                        .arg(ui->lineEdit_cost->text())
                        );

            if(!(queryAdd.exec()))
            {
                QString error = "Adding ACK in aviation failed: " + queryAdd.lastError().text();
                qDebug() << "Adding ACK in aviation failed: " << queryAdd.lastError();
                ui->statusbar->showMessage(error);
            }

            printAllAircrafts_T_aviation();
        }
        else
        {
            QString error = "Adding ACK in aviation failed: wrong data wrote!\n";
            qDebug() << "Adding ACK in aviation failed: wrong data wrote!\n";
            ui->statusbar->showMessage(error);
        }
    }
}


void MainWindow::on_pushButton_deleteACK_clicked()
{
    int index = ui->listWidget_availableACK->currentRow();
    if (index <= vector_T_aviation.size())
    {
        QString key_aviation = vector_T_aviation[index].key_aviation;
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM aviation WHERE key_aviation = (:key_aviation)");
        queryDelete.bindValue(":key_aviation", key_aviation); // второй способ вставлять данные bindValue
        if(!(queryDelete.exec())) // exec выполняет то, что заложено в строках, выдает 1 или 0
        {
            QString error = "Deleting aircraft from aviation failed: " + queryDelete.lastError().text();
            qDebug() << "Deleting aircraft from aviation failed: " << queryDelete.lastError();
            ui->statusbar->showMessage(error);
        }

        printAllAircrafts_T_aviation();
    }
}


void MainWindow::on_listWidget_enemy_itemSelectionChanged()
{
    int i;
    for (i = 0; i < vector_T_enemy.size(); i++)
    {
        if (i == ui->listWidget_enemy->currentRow())
        {
            ui->lineEdit_enemyName->setText(vector_T_enemy[i].zrk_name);
            ui->lineEdit_enemyTargetingSystem->setText(vector_T_enemy[i].targeting_system);
            ui->lineEdit_enemyDestructionRangeMin->setText(vector_T_enemy[i].min_destr_range);
            ui->lineEdit_enemyDestructionRangeMax->setText(vector_T_enemy[i].max_destr_range);
            ui->lineEdit_enemyAAGMVelocity->setText(vector_T_enemy[i].AAGM_velocity);
            ui->lineEdit_enemyMaxHeight->setText(vector_T_enemy[i].max_height);

            break;
        }
    }
}

void MainWindow::on_pushButton_addEnemy_clicked()
{
    if (ui->lineEdit_enemyName->text().isEmpty())
    {
        ui->statusbar->showMessage("Название не заполнено!");
    }
    else if (ui->lineEdit_enemyTargetingSystem->text().isEmpty())
    {
        ui->statusbar->showMessage("Система наведения не заполнена");
    }
    else if (ui->lineEdit_enemyDestructionRangeMin->text().isEmpty() ||
             ui->lineEdit_enemyDestructionRangeMax->text().isEmpty() )
    {
        ui->statusbar->showMessage("Дальность поражения не заполнена");
    }
    else if (ui->lineEdit_enemyAAGMVelocity->text().isEmpty())
    {
        ui->statusbar->showMessage("Скорость ЗУР не заполнена");
    }
    else if (ui->lineEdit_enemyMaxHeight->text().isEmpty())
    {
        ui->statusbar->showMessage("Максимальная высота не заполнена");
    }
    else
    {
        if (checkEnemies_T_enemy())
        {
            ui->statusbar->clearMessage();

            QSqlQuery queryAdd;
            queryAdd.prepare(
                        QString("INSERT INTO zrk (zrk_name, targeting_system, min_destr_range, max_destr_range, AAGM_velocity, max_height) VALUES ('%1', '%2', '%3', '%4', '%5', '%6');")
                        .arg(ui->lineEdit_enemyName->text())
                        .arg(ui->lineEdit_enemyTargetingSystem->text())
                        .arg(ui->lineEdit_enemyDestructionRangeMin->text())
                        .arg(ui->lineEdit_enemyDestructionRangeMax->text())
                        .arg(ui->lineEdit_enemyAAGMVelocity->text())
                        .arg(ui->lineEdit_enemyMaxHeight->text())
                        );

            if(!(queryAdd.exec()))
            {
                QString error = "Adding enemy in zrk failed: " + queryAdd.lastError().text();
                qDebug() << "Adding enemy in zrk failed: " << queryAdd.lastError();
                ui->statusbar->showMessage(error);
            }

            printAllEnemies_T_enemy();
        }
        else
        {
            QString error = "Adding enemy in zrk failed: wrong data wrote!\n";
            qDebug() << "Adding enemy in zrk failed: wrong data wrote!\n";
            ui->statusbar->showMessage(error);
        }
    }
}


void MainWindow::on_pushButton_deleteEnemy_clicked()
{
    int index = ui->listWidget_enemy->currentRow();
    if (index <= vector_T_enemy.size())
    {
        QString key_zrk = vector_T_enemy[index].key_zrk;
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM zrk WHERE key_zrk = (:key_zrk)");
        queryDelete.bindValue(":key_zrk", key_zrk); // второй способ вставлять данные bindValue
        if(!(queryDelete.exec())) // exec выполняет то, что заложено в строках, выдает 1 или 0
        {
            QString error = "Deleting enemy from zrk failed: " + queryDelete.lastError().text();
            qDebug() << "Deleting enemy from zrk failed: " << queryDelete.lastError();
            ui->statusbar->showMessage(error);
        }

        printAllEnemies_T_enemy();
    }
}


void MainWindow::on_pushButton_clearEnemy_clicked()
{
    ui->lineEdit_enemyName->clear();
    ui->lineEdit_enemyTargetingSystem->clear();
    ui->lineEdit_enemyDestructionRangeMin->clear();
    ui->lineEdit_enemyDestructionRangeMax->clear();
    ui->lineEdit_enemyAAGMVelocity->clear();
    ui->lineEdit_enemyMaxHeight->clear();
}

