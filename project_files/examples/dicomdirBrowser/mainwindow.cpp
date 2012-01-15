#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	ui->treeView->setModel(&m_directoryModel);

	connect(ui->actionOpen, SIGNAL(triggered()), &m_directoryModel, SLOT(load()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
