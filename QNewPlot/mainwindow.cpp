#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_CreatePlot_clicked(double beginX, double endX, double pointX, double pointY, char* labelX, char* labelY)
{
	//Рисуем график

	//int N = (endX - beginX) / step + 2; //Вычисляем количество точек, которые будем отрисовывать


	//Добавляем один график в widget
	ui->widget->addGraph();
	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->widget->graph(0)->setData(x, y);

	ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
	ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
	//формируем вид точек
	ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

	//Подписываем оси Ox и Oy
	ui->widget->xAxis->setLabel(labelX);
	ui->widget->yAxis->setLabel(labelY);

	//Установим область, которая будет показываться на графике
	ui->widget->xAxis->setRange(beginX, endX);//Для оси Ox

	//Для показа границ по оси Oy сложнее, так как надо по правильному
	//вычислить минимальное и максимальное значение в векторах
	double minY = y[0], maxY = y[0];
	for (int i = 1; i < N; i++)
	{
		if (y[i] < minY) minY = y[i];
		if (y[i] > maxY) maxY = y[i];
	}
	ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

	//И перерисуем график на нашем widget
	ui->widget->replot();
}

void MainWindow::on_Clear_clicked()
{
	ui->widget->clearGraphs();//Если нужно, но очищаем все графики
}

void MainWindow::add_point(double pointX, double pointY) 
{
	QVector<double> x(1), y(1); //Массивы координат точек

	x[0] = pointX;
	y[0] = pointY;

	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->widget->graph(0)->setData(x, y);
}