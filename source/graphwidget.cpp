#include "graphwidget.h"

extern int nodes;

#include <iostream>

class Node;
GraphWidget::GraphWidget(pro::list<Person>& data, QWidget* parent)
    : QGraphicsView(parent)
{
    forcesEnabled = false;
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);            // ^
    setWindowTitle(tr("Elastic Nodes"));            // | some basic preconfiguring

    std::vector<Node*> nodes;
    for (pro::list<Person>::iterator i = data.begin( ); i != data.end( ); ++i)
    {   //  adding nodes to graph
        nodes.push_back(new Node(this));
        nodes.back( )->addNames(i->getData( ));
        scene->addItem(nodes.back( ));
        i->friends_ptr.push_back(nodes.back( ));
    }

    int i_ = 0;
    for (auto i : data)
    {   // adding edges to graph
        //! possible bloat
        for (auto j : i.getFriends( ))
        {
            int z = 0;
            for (auto k : data)
            {
                if (k.getData( ) == j->getData( ))
                {
                    break;
                }
                z++;
            }
            scene->addItem(new Edge(nodes[i_], nodes[z]));
        }
        i_++;
    }

    for (int i = 0; i < nodes.size( ); i++) //! change to populate in circle around one node
    {   // setting positions to not merge nodes into one
        nodes[i]->setPos(50 + i * 30, 50 - i * 30);
    }

    centerNode = nodes.back( );
    centerNode->setPos(0, 0);

    QPushButton* button = new QPushButton;
    button->setGeometry(QRect(72, -200, 128, 32));
    button->setText("fizyka");
    QObject::connect(button, SIGNAL(clicked( )), this, SLOT(buttonClicked( )));
    scene->addWidget(button);
}

void GraphWidget::itemMoved( )
{
    if (!timerId)
        timerId = startTimer(1);
}

void GraphWidget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key( ))
    {
        case Qt::Key_Up:
            centerNode->moveBy(0, -20);
            break;
        case Qt::Key_Down:
            centerNode->moveBy(0, 20);
            break;
        case Qt::Key_Left:
            centerNode->moveBy(-20, 0);
            break;
        case Qt::Key_Right:
            centerNode->moveBy(20, 0);
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);

    QList<Node*> nodes;
    const QList<QGraphicsItem*> items = scene( )->items( );
    for (QGraphicsItem* item : items)
    {
        if (Node* node = qgraphicsitem_cast<Node*>(item))
            nodes << node;
    }

    if (forcesEnabled)
    {
        for (Node* node : std::as_const(nodes))
            node->calculateForces( );

        bool itemsMoved = false;
        for (Node* node : std::as_const(nodes))
        {
            if (node->advancePosition( ))
                itemsMoved = true;
        }

        if (!itemsMoved)
        {
            killTimer(timerId);
            timerId = 0;
        }
    }
}

void GraphWidget::wheelEvent(QWheelEvent* event)
{
    scaleView(pow(2., -event->angleDelta( ).y( ) / 240.0));
}

void GraphWidget::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect( );
    QRectF rightShadow(sceneRect.right( ), sceneRect.top( ) + 5, 5, sceneRect.height( ));
    QRectF bottomShadow(sceneRect.left( ) + 5, sceneRect.bottom( ), sceneRect.width( ), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft( ), sceneRect.bottomRight( ));
    gradient.setColorAt(0, Qt::lightGray);
    gradient.setColorAt(1, Qt::gray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left( ) + 4, sceneRect.top( ) + 4,
                    sceneRect.width( ) - 4, sceneRect.height( ) - 4);
    QString message(tr("Niezłe gówno"));

    QFont font = painter->font( );
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform( ).scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width( );
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::buttonClicked( )
{
    forcesEnabled = !forcesEnabled;
}
