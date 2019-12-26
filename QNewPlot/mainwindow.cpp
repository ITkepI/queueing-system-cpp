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

public double begin = -1; //Начало интервала, где рисуем график по оси Ox
public double end = 1; //Конец интервала, где рисуем график по оси Ox
public double step = 0.1; //Шаг, с которым будем пробегать по оси Ox

void MainWindow::on_PushButton_clicked(double begin, double end, char* labelX, char* labelY)
{
	//Рисуем график

		//Сгенерируем данные
		//Для этого создадим два массива точек:
		//один для созранения x координат точек,
		//а второй для y соответственно

	int N = (end - begin) / step + 2; //Вычисляем количество точек, которые будем отрисовывать
	QVector<double> x(N), y(N); //Массивы координат точек

	//Вычисляем наши данные
	int i = 0;
	for (double X = begin; X <= end; X += step)//Пробегаем по всем точкам
	{
		x[i] = X;
		y[i] = X * X;//Формула нашей функции
		i++;
	}

	//Добавляем один график в widget
	ui->widget->addGraph();
	//Говорим, что отрисовать нужно график по нашим двум массивам x и y
	ui->widget->graph(0)->setData(x, y);

	ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
	ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
	//формируем вид точек
	ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

	//Подписываем оси Ox и Oy
	ui->widget->xAxis->setLabel("x");
	ui->widget->yAxis->setLabel("y");

	//Установим область, которая будет показываться на графике
	ui->widget->xAxis->setRange(begin, end);//Для оси Ox

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