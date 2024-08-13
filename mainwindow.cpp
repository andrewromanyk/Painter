#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include "dialoghelp.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleSheet("background-color: lightblue;");
    ui->gridLayoutWidget->setStyleSheet("background-color: white");
    ui->label->setStyleSheet("background-color: white");
    ui->gridLayoutWidget = canvas;

    canvas = new Canvas(this);
    ui->gridLayout->addWidget(canvas);

    connect(canvas, &Canvas::mousePositionChanged, this, &MainWindow::MousePos);
    setWindowTitle("Painter");
    setFixedSize(size());
    connect(canvas, &Canvas::currenyColorChanged, this, &MainWindow::updateColor);

    QIcon qicon("../../palette.png");
    ui->toolButton->setIcon(qicon);
    ui->toolButton->setIconSize(QSize(32, 32));
    ui->sizelabel->setText(QString::number(ui->horizontalSlider->sliderPosition()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->checkState()) canvas->setShape(Canvas::Shape::Line);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->checkState()) canvas->setShape(Canvas::Shape::Square);
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if (ui->checkBox_3->checkState()) canvas->setShape(Canvas::Shape::Circle);
}


void MainWindow::on_actionSave_as_PNG_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG Images (*.png)"));
    if (!fileName.isEmpty()) {
        canvas->saveImage(fileName);
    }
}

void MainWindow::MousePos(int x, int y)
{
    ui->label->setText(QString("%1, %2").arg(x).arg(y));
}


void MainWindow::on_actionTools_triggered()
{
    DialogHelp* help = new DialogHelp();
    help->setWindowTitle("Help");
    help->show();
}


void MainWindow::on_toolButton_clicked()
{
    QColor color = QColorDialog::getColor(canvas->getColor(), this, "Choose Drawing Color");
    if (color.isValid()) {
        canvas->setColor(color);
    }
}

void MainWindow::updateColor(const QColor& color) {
    ui->toolButton->setStyleSheet(QString("background-color: %1").arg(canvas->getColor().name()));
}


void MainWindow::on_horizontalSlider_sliderReleased()
{
    qDebug() << ui->horizontalSlider->sliderPosition();
    emit sizeChanged(ui->horizontalSlider->sliderPosition());
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->sizelabel->setText(QString::number(ui->horizontalSlider->sliderPosition()));
}

