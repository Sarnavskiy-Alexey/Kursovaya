#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::FromDB_T_enemy()
{
    ui->listWidget_enemy->clear();
    int i;
    for (i = 0; i < vector_T_enemy.size(); i++)
    {
        ui->listWidget_enemy->addItem(vector_T_enemy[i].zrk_name);
    }
}
