#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertar_clicked()
{
    string cadena=ui->cadena->text().toStdString();
    if(cadena=="")
        cout<<"cadena vacia"<<endl;
    else
        keywords.push_back(cadena);
}

void MainWindow::on_construir_clicked()
{
    //***************************************

    string text=ui->text->text().toStdString();
    int n=keywords.size();
    string arr[n];
    for (int i=0;i<n;i++)
    {
        arr[i]=keywords[i];
        cout<<arr[i]<<endl;
    }

    int k = sizeof(arr)/sizeof(arr[0]);

    afd.buscar_palbras(arr, k, text);
    //cout<<"termino de guardar dic"<<endl;
    //cout<<"texto "<<t<<endl;
    //afnd.buscar_palbras(arr1, k, t,afnd);

    // afnd.generar_dot(afnd);
    afd.generar_dot(afd);
    QImage F;
    F.load("grafo.png");
    ui->dot->setPixmap(QPixmap::fromImage(F));
    QString resul=QString::fromStdString(afd.resultado);
    //cout<<afd.resultado<<endl;
    //QString resul=QString::fromStdString(afnd.resultado);
    //cout<<afd.resultado<<endl;
    ui->resul->setText(resul);


}
