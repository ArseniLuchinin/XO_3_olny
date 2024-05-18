#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::button_to_index(){
    buttons.append(ui->pushButton);
    buttons.append(ui->pushButton_2);
    buttons.append(ui->pushButton_3);
    buttons.append(ui->pushButton_4);
    buttons.append(ui->pushButton_5);
    buttons.append(ui->pushButton_6);
    buttons.append(ui->pushButton_7);
    buttons.append(ui->pushButton_8);
    buttons.append(ui->pushButton_9);
    int a = -1;
    for(XO_Button* &p : buttons){
        p->set_index(++a);
        connect(p, SIGNAL(clicked()), SLOT(on_pushButton_clicked()));
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->verticalLayout_2->addWidget(new QPushButton("Meow"));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_to_index();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    XO_Button *buttonSender = qobject_cast<XO_Button*>(sender());
    buttons[buttonSender->get_index()]->setText(QString::number(buttonSender->get_index()));
}

