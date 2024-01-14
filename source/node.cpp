#include "node.h"
#include "edge.h"
#include "graphwidget.h"
#include <iostream>


size_t Node::count = 0;

class Edge;
Node::Node(GraphWidget* graphWidget)  // constructor
    : graph(graphWidget)
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

/**
 * @brief Adding edge to this node.
 * @param edge Edge which is connetced to this node.
 */
void Node::addEdge(Edge* edge)
{
    edgeList << edge;
    edge->adjust( );
}

/**
 * @brief Function that simulates some physics interactions between nodes and edges.
 */
void Node::calculateForces( )
{
    if (!scene( ) || scene( )->mouseGrabberItem( ) == this)
    {
        newPos = pos( );
        return;
    }
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    const QList<QGraphicsItem*> items = scene( )->items( );
    for (QGraphicsItem* item : items)
    {
        Node* node = qgraphicsitem_cast<Node*>(item);
        if (!node)
            continue;
        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x( );
        qreal dy = vec.y( );
        double l = (2.0 + 2.0 * (Node::count / 15)) * (dx * dx + dy * dy);
        if (l > 0)
        {
            xvel += (dx * 150.0 / l);
            yvel += (dy * 150.0 / l);
        }
    }
    // Now subtract all forces pulling items together
    double weight = (edgeList.size( ) + 1) * 80 + (Node::count * (Node::count / 3));
    for (const Edge* edge : std::as_const(edgeList))
    {
        QPointF vec;
        if (edge->sourceNode( ) == this)
            vec = mapToItem(edge->destNode( ), 0, 0);
        else
            vec = mapToItem(edge->sourceNode( ), 0, 0);
        xvel -= vec.x( ) / weight;
        yvel -= vec.y( ) / weight;
    }
    // Then set new positions
    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;
    QRectF sceneRect = scene( )->sceneRect( );
    newPos = pos( ) + QPointF(xvel, yvel);
    newPos.setX(qMin(qMax(newPos.x( ), sceneRect.left( ) + 10), sceneRect.right( ) - 10));
    newPos.setY(qMin(qMax(newPos.y( ), sceneRect.top( ) + 10), sceneRect.bottom( ) - 10));
}

QRectF Node::boundingRect( ) const
{
    qreal adjust = 2;
    return QRectF(-300 - adjust, -300 - adjust, 600 + adjust, 600 + adjust);
}

bool Node::advancePosition( )
{
    if (newPos == pos( ))
        return false;

    setPos(newPos);
    return true;
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);

    // painter->drawEllipse(-7, -7, 20, 20); // shadows
    double weight = double(edgeList.size( ) + 1) / 20;
    QRadialGradient gradient(-9 - 9 * weight, -9 - 9 * weight, 30 + 30 * weight);
    if (option->state & QStyle::State_Sunken)
    {
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    }
    else
    {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);

    // painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-30 - 30 * weight, -30 - 30 * weight, 60 + 60 * weight, 60 + 60 * weight);

    QFont font("Sans Serif", 15);
    QFontMetrics fm(font);
    painter->setFont(font);
    QRect rectText = fm.boundingRect(names.c_str( ));
    rectText.moveCenter(QPoint(-1, -1));

    painter->setBrush(Qt::white);
    painter->drawRect(rectText);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawText(boundingRect( ), Qt::AlignCenter, names.c_str( ));
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant& value)
{
    switch (change)
    {
        case ItemPositionHasChanged:
            for (Edge* edge : std::as_const(edgeList))
                edge->adjust( );
            graph->itemMoved( );
            break;
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    update( );
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    update( );
    QGraphicsItem::mouseReleaseEvent(event);
}

QPainterPath Node::shape( ) const
{
    QPainterPath path;
    double weight = (edgeList.size( ) + 1) / 20;
    path.addEllipse(-30 - 30 * weight, -30 - 30 * weight, 60 + 60 * weight, 60 + 60 * weight);
    return path;
}

/**
 * @brief Returns list of edges connected to this node.
 * @return QList of every edge connected to this node.
 */
QList<Edge*> Node::edges( ) const
{
    return edgeList;
}

/**
 * @brief Function used to change name displayed ont this node.
 * @param input Name that shall be displayed.
 */
void Node::addNames(std::string input)
{
    names = input;
}

void Node::linkPerson(Person* person)
{
    persona = person;
}

Person* Node::getLinkedPerson( )
{
    return persona;
}
