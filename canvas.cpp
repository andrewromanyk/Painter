#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMimeData>
#include <QImageReader>
#include "mainwindow.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent), drawing(false)
{
    setMinimumSize(780, 480);
    pixmap = QPixmap(size());
    pixmap.fill(Qt::white);
    setMouseTracking(true);
    setAcceptDrops(true);
    connect((MainWindow*) parentWidget(), &MainWindow::sizeChanged, this, &Canvas::setBrushSize);
}

void Canvas::setShape(Shape shape)
{
    currentShape = shape;
}

void Canvas::saveImage(const QString &fileName)
{
    pixmap.save(fileName);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    if (drawing) {
        painter.setPen(QPen(currentColor, brushSize));
        //painter.setPen();
        switch (currentShape) {
        case Shape::Line:
            painter.drawLine(startPoint, endPoint);
            break;
        case Shape::Circle: {
            int radius = std::sqrt(std::pow(endPoint.x() - startPoint.x(), 2) + std::pow(endPoint.y() - startPoint.y(), 2));
            painter.drawEllipse(startPoint, radius, radius);
            break;
        }
        case Shape::Square: {
            int size = std::max(std::abs(endPoint.x() - startPoint.x()), std::abs(endPoint.y() - startPoint.y()));
            int height = endPoint.y() - startPoint.y();
            int width = endPoint.x() - startPoint.x();
            painter.drawRect(startPoint.x(), startPoint.y(), width, height);
            break;
        }
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        startPoint = event->pos();
        endPoint = startPoint;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    emit mousePositionChanged(event->pos().x(), event->pos().y());
    if (drawing) {
        endPoint = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        endPoint = event->pos();
        drawing = false;

        QPainter painter(&pixmap);
        painter.setPen(QPen(currentColor, brushSize));
        switch (currentShape) {
        case Shape::Line:
            painter.drawLine(startPoint, endPoint);
            break;
        case Shape::Circle: {
            int radius = std::sqrt(std::pow(endPoint.x() - startPoint.x(), 2) + std::pow(endPoint.y() - startPoint.y(), 2));
            painter.drawEllipse(startPoint, radius, radius);
            break;
        }
        case Shape::Square: {
            int size = std::max(std::abs(endPoint.x() - startPoint.x()), std::abs(endPoint.y() - startPoint.y()));
            int height = endPoint.y() - startPoint.y();
            int width = endPoint.x() - startPoint.x();
            painter.drawRect(startPoint.x(), startPoint.y(), width, height);
            break;
        }
        }
        update();
    }
}


void Canvas::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urlList = event->mimeData()->urls();
        if (urlList.size() == 1) {
            QString filePath = urlList.at(0).toLocalFile();
            if (filePath.endsWith(".png") || filePath.endsWith(".jpg") || filePath.endsWith(".jpeg")) {
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void Canvas::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QList<QUrl> urlList = event->mimeData()->urls();
        if (urlList.size() == 1) {
            QString filePath = urlList.at(0).toLocalFile();
            if (filePath.endsWith(".png") || filePath.endsWith(".jpg") || filePath.endsWith(".jpeg")) {
                event->acceptProposedAction();
                return;
            }
        }
    }
    event->ignore();
}

void Canvas::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (urlList.size() == 1) {
            QString filePath = urlList.at(0).toLocalFile();
            if (filePath.endsWith(".png") || filePath.endsWith(".jpg") || filePath.endsWith(".jpeg")) {
                QPixmap newPixmap(filePath);
                if (!newPixmap.isNull()) {
                    // Resize pixmap to fit the canvas while maintaining aspect ratio
                    // Resize pixmap to fit the canvas while maintaining aspect ratio
                    QPainter painter(&pixmap);
                    QPoint position(0, 0);
                    pixmap.fill(Qt::white);
                    painter.drawPixmap(position, newPixmap.scaled(pixmap.size(), Qt::KeepAspectRatio));
                   // pixmap = newPixmap.scaled(size(), Qt::KeepAspectRatio);
                    update();
                    event->acceptProposedAction();
                    return;
                }
            }
        }
    }
    event->ignore();
}
