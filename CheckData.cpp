#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DECIMAL 10

bool MainWindow::checkAircrafts_T_aviation()
{
    bool right_data = true;
    bool ok = true;

    QString name = ui->lineEdit_name->text();
    QString country = ui->lineEdit_country->text();
    QString wingspan = ui->lineEdit_wingspan->text();
    QString mass = ui->lineEdit_mass->text();
    QString velocity = ui->lineEdit_velocity->text();
    QString armamentUnits = ui->lineEdit_armamentUnits->text();
    QString combatRadius = ui->lineEdit_combatRadius->text();
    QString flightRange = ui->lineEdit_flightRange->text();
    QString cost = ui->lineEdit_cost->text();

    ok = (name.size() <= 21);
    right_data &= ok;

    ok = (country.size() <= 21);
    right_data &= ok;

    wingspan.toDouble(&ok);
    right_data &= ok;

    mass.toDouble(&ok);
    right_data &= ok;

    velocity.toDouble(&ok);
    right_data &= ok;

    armamentUnits.toUInt(&ok, DECIMAL);
    right_data &= ok;

    combatRadius.toDouble(&ok);
    right_data &= ok;

    flightRange.toDouble(&ok);
    right_data &= ok;

    cost.toDouble(&ok);
    right_data &= ok;

    return right_data;
}

bool MainWindow::checkEnemies_T_enemy()
{
    bool right_data = true;
    bool ok = true;

    QString enemyName = ui->lineEdit_enemyName->text();
    QString enemyTargetingSystem = ui->lineEdit_enemyTargetingSystem->text();
    QString enemyDestructionRangeMin = ui->lineEdit_enemyDestructionRangeMin->text();
    QString enemyDestructionRangeMax = ui->lineEdit_enemyDestructionRangeMax->text();
    QString enemyAAGMVelocity = ui->lineEdit_enemyAAGMVelocity->text();
    QString enemyMaxHeight = ui->lineEdit_enemyMaxHeight->text();

    ok = (enemyName.size() <= 21);
    right_data &= ok;

    ok = (enemyTargetingSystem.size() <= 21);
    right_data &= ok;

    enemyDestructionRangeMin.toDouble(&ok);
    right_data &= ok;

    enemyDestructionRangeMax.toDouble(&ok);
    right_data &= ok;

    enemyAAGMVelocity.toDouble(&ok);
    right_data &= ok;

    enemyMaxHeight.toDouble(&ok);
    right_data &= ok;

    return right_data;
}
