#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QLabel>
#include <QGraphicsTextItem>
#include <QObject>

#include "person.h"
#include "mainwindow.h"

class MainWindow;
class Person;
class Edge;
class GraphWidget;

/**
 * @brief Node is class representing single node on graph. Has name, and is linked by edge to another nodes.
 */
class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    static size_t count;
    std::string names; //! change to pravate
    Node(GraphWidget* graphWidget, MainWindow* parent = nullptr);

    void addEdge(Edge* edge);
    QList<Edge*> edges( ) const;

    enum { Type = UserType + 1 };
    int type( ) const override { return Type; }

    void calculateForces( );
    bool advancePosition( );

    QRectF boundingRect( ) const override;
    QPainterPath shape( ) const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void addNames(std::string input);
    void linkPerson(Person* person);
    Person* getLinkedPerson( );

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void mousePressed(Node* node);

private:
    QList<Edge*> edgeList;
    QPointF newPos;
    GraphWidget* graph;
    Person* persona;

};

#endif // NODE_H
