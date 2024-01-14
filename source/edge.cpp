#include "edge.h"

#include <QPainter>

/**
 * @brief Retruns Node that is source in ths edge.
 * @return Pointer to Node.
 */
Node* Edge::sourceNode( ) const
{
    return source;
}

/**
 * @brief Retruns Node that is destination in ths edge.
 * @return Pointer to Node.
 */
Node* Edge::destNode( ) const
{
    return dest;
}

/**
 * @brief Function to adjust starting and ending points of edges, to not overlap with nodes.
 * Some magic math inside.
 */
void Edge::adjust( )
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length( );

    prepareGeometryChange( );
    double weightS = double(source->edges( ).size( ) + 1) / 20;   // "weight"(count of edges)of source
    double weightD = double(dest->edges( ).size( ) + 1) / 20;     // -||-                       dest
    if (length > qreal(20.))
    {
        QPointF edgeOffsetS((line.dx( ) * (30 + 30 * weightS)) / length, (line.dy( ) * (30 + 30 * weightS)) / length);               // very sophisticated math dont really know what going on
        QPointF edgeOffsetD((line.dx( ) * (30 + 30 * weightD)) / length, (line.dy( ) * (30 + 30 * weightD)) / length);
        sourcePoint = line.p1( ) + edgeOffsetS;
        destPoint = line.p2( ) - edgeOffsetD;
    }
    else
    {
        sourcePoint = destPoint = line.p1( );
    }
}

QRectF Edge::boundingRect( ) const
{
    if (!source || !dest)
        return QRectF( );

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x( ) - sourcePoint.x( ),
                                      destPoint.y( ) - sourcePoint.y( )))
        .normalized( )
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length( ), qreal(0.)))
        return;
    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
    // Draw the arrows
}

Edge::Edge(Node* sourceNode, Node* destNode)
    : source(sourceNode), dest(destNode)
{
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    adjust( );
}
