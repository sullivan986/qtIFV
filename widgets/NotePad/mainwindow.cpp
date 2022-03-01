#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,&QAction::triggered,this,&::MainWindow::action_new);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action_new()
{
    QString filename = QFileDialog::getOpenFileName(this, "open the file");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "warning", "Can not open file : " + file.errorString());
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->clear();
    ui->textEdit->setText(text);
    file.close();
}
