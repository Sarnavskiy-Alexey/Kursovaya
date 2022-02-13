#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::FromDB_T_aviation()
{
    ui->listWidget_availableACK->clear();
    int i;
    for (i = 0; i < vector_T_aviation.size(); i++)
    {
        ui->listWidget_availableACK->addItem(vector_T_aviation[i].name);
    }
}
