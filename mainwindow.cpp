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
    ui->stackedWidget->setCurrentIndex(0);
    ui->verticalLayout_2->addWidget(new QPushButton("Meow"));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_to_index();
    game = new Game_Client();
    connect(game, &Game_Client::new_figure_position_from_server, this, &MainWindow::new_positon_from_server);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}


void MainWindow::on_pushButton_clicked()
{
    XO_Button *buttonSender = qobject_cast<XO_Button*>(sender());
    buttonSender->setText(QString::number(buttonSender->get_index()));
    game->send_pos_to_server(buttonSender->get_index(), 1);
}

void MainWindow::new_positon_from_server(){
    buttons[game->get_new_pos()]->setText(QString(game->get_game_subbol()));
}
