#ifndef EDGE_H
#define EDGE_H

#include "node.h"
class Node;
/**
 * @brief Edge is a class representing single edge on graph. Every edge has source and destination.
 */
class Edge : public QGraphicsItem
{
public:
    Edge(Node* sourceNode, Node* destNode);

    Node* sourceNode( ) const;
    Node* destNode( ) const;

    void adjust( );

    enum { Type = UserType + 2 };
    int type( ) const override { return Type; }

protected:
    QRectF boundingRect( ) const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    Node* source, * dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
};
#endif // EDGE_H
