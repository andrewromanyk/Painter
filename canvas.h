#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    enum class Shape { Line, Circle, Square };

    explicit Canvas(QWidget *parent = nullptr);
    void setShape(Shape shape);
    void saveImage(const QString &fileName);
    QColor getColor() {return currentColor;};
    void setColor(QColor color) {
        currentColor = color;
        emit currenyColorChanged(color);}

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
private slots:
    void setBrushSize(int s) {brushSize = s;};

signals:
    void mousePositionChanged(int x, int y);
    void currenyColorChanged(const QColor &color);
private:
    QColor currentColor;
    Shape currentShape;
    bool drawing;
    QPoint startPoint, endPoint;
    QPixmap pixmap;
    int brushSize;
};

#endif // CANVAS_H
