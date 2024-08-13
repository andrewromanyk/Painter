#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvas.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_actionSave_as_PNG_triggered();

    void MousePos(int x, int y);
    void on_actionTools_triggered();

    void on_toolButton_clicked();
    void updateColor(const QColor& color);

    void on_horizontalSlider_sliderReleased();

    void on_horizontalSlider_sliderMoved(int position);

signals:
    void sizeChanged(int);
private:
    Ui::MainWindow *ui;
    Canvas *canvas;
};
#endif // MAINWINDOW_H
