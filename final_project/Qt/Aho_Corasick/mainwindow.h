#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "automata.h"
#include "automata_noD.h"
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    vector<string > keywords;
    automata<int,char > afd;
    automata_noD<int,char> afnd;

private slots:
    void on_insertar_clicked();

    void on_construir_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
