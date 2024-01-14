#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QObject>
#include <QKeyEvent>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QRandomGenerator>
#include <QTime>
#include <algorithm>

#include "node.h"
#include "edge.h"
#include "list.h"
#include "person.h"

class Node;
class Person;

/**
 * @brief GraphWidget is class that represents whole social graph. Inherited from QGraphicsView. Containg Q_OBJECT macro.
 */
class GraphWidget : public QGraphicsView
{
    Q_OBJECT    // dont know how this works :) some metaprogramming

public:
    GraphWidget(QVector<Person>& data, QWidget* parent = nullptr);

    void itemMoved( );
    bool forcesEnabled;

public slots:
    void buttonClicked( );

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent* event) override;
#endif
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId = 0;
    Node* centerNode;
};

#endif // GRAPHWIDGET_H
