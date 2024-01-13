#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QStyle>
#include <QLabel>
#include <QGraphicsTextItem>
class Edge;
class GraphWidget;

/**
 * @brief Node is class representing single node on graph. Has name, and is linked by edge to another nodes.
 */
class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addNames(std::string input);


protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
    std::string names;
};

#endif // NODE_H
