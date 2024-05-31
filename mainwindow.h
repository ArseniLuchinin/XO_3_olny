#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "game_logic.h"
#include "xo_button.h"
#include "lobbie_button.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void new_positon_from_server();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    void clear_map();
    Game_Client *game;
    Ui::MainWindow *ui;
    QList <XO_Button*>buttons{};
    void button_to_index();
    void add_lobby_bytton();

    void clear_lobbies_laoyt();
};
#endif // MAINWINDOW_H
