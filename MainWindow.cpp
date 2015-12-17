#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "MainView.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto glView = new MainView(this);

    ui->verticalLayout->addWidget(glView);

    connect(ui->actionCone, SIGNAL(triggered()), glView, SLOT(setCone()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
