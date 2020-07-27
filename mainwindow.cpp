#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = new QTcpServer(this);
    _server->listen(QHostAddress::Any,_port);
    connect(_server, SIGNAL(newConnection()), SLOT(myNewConnection()));
    //ui->widgetPlot->clearGraphs();
    ui->widgetPlot->setInteraction(QCP::iRangeDrag, true);
    ui->widgetPlot->setInteraction(QCP::iRangeZoom, true);
    ui->widgetPlot->addGraph();
    //ui->widgetPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    //ui->widgetPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widgetPlot->xAxis->setLabel("X");
    ui->widgetPlot->yAxis->setLabel("Y");
    ui->widgetPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->widgetPlot->graph(0)->setBrush(QBrush(QColor(0,0,255,20)));
    ui->widgetPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widgetPlot->setWindowTitle("Data thread");
    connect(ui->widgetPlot,SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGrahp(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myNewConnection()
{
    _socket = _server->nextPendingConnection();
    setWindowTitle("Server");
    connect(_socket,SIGNAL(readyRead()), SLOT(myReadyRead()));
}

void MainWindow::myReadyRead()
{
    QDataStream in(_socket);
    int tempPointX;
    int tempPointY;
    in >> tempPointX;
    in >> tempPointY;
    _dataY.append(tempPointX);
    _dataX.append(tempPointY);
    ui->widgetPlot->graph(0)->setData(_dataX, _dataY);
    ui->widgetPlot->replot();
    ui->widgetPlot->update();
}

void MainWindow::clearData()
{
    _dataX.clear();
    _dataY.clear();
}

void MainWindow::on_clearButton_clicked()
{
    clearData();
}
