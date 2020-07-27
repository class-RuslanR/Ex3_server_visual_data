#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

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
    void myNewConnection();
    void myReadyRead();
    void clearData();
    void on_clearButton_clicked();
private:
    Ui::MainWindow *ui;
    QTcpServer* _server = nullptr;
    QTcpSocket* _socket = nullptr;
    uint16_t _port = 2525;
    QVector<double> _dataX, _dataY;
};
#endif // MAINWINDOW_H
