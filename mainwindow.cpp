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
    ui->pushButton->set_index(0);
    for(int i = 1; i < buttons.length(); ++i){
        buttons[i]->set_index(i);
        connect((buttons[i]), SIGNAL(clicked()), SLOT(on_pushButton_clicked()));
    }

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    button_to_index();
    game = new Game_Client();
    connect(game, &Game_Client::new_figure_position_from_server, this, &MainWindow::new_positon_from_server);
    connect(game, &Game_Client::new_lobbie, this, &MainWindow::add_lobby_bytton);
    connect(game, &Game_Client::new_figure, this,
            [this](){
             ui->label->setText(game->get_game_subbol());
        });
    game->send_lobbies_reqest();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}


void MainWindow::on_pushButton_clicked()
{
    //if(game->is_my_move()){
        XO_Button *buttonSender = qobject_cast<XO_Button*>(sender());
        game->send_pos_to_server(buttonSender->get_index(), 1);
    //}
}

void MainWindow::new_positon_from_server(){
    buttons[game->get_new_pos()]->setText(QString(game->get_current_game_subbol()));
}

void MainWindow::add_lobby_bytton(){
    lobbie_button* lb = new lobbie_button(
                game->get_new_lobbie_id(),
                "Game lobby #" +  QString::number(game->get_new_lobbie_id())
                );
    ui->verticalLayout_2->addWidget(lb);
    connect(lb, &QPushButton::clicked, this, [lb, this](){
        game->set_id(lb->get_lobby_id());
        ui->stackedWidget->setCurrentIndex(0);

    });
}

void MainWindow::on_pushButton_10_clicked()
{
    clear_lobbies_laoyt();
    game->send_lobbies_reqest();
    qDebug() << game->get_id();
}

void MainWindow::clear_lobbies_laoyt(){
    QLayoutItem *child;
     while ((child = ui->verticalLayout_2->takeAt(0)) != 0) {
         ui->verticalLayout_2->removeItem(child);
         delete child;
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

