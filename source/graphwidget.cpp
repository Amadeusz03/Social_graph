#include "graphwidget.h"

#include <iostream>

class Node;
GraphWidget::GraphWidget(QVector<Person*>* data, MainWindow* parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-1000, -1000, 2000, 2000);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);            // ^
    setWindowTitle(tr("Elastic Nodes"));            // | some basic preconfiguring

    if (!data)
    {
        return;
    }
    Node::count = 0;
    for (QVector<Person*>::iterator i = data->begin( ); i != data->end( ); ++i)
    {   //  adding nodes to graph
        nodes.push_back(new Node(this, parent));
        Node::count++;
        nodes.back( )->linkPerson(*i);
        nodes.back( )->addNames((*i)->getData( ));
        scene->addItem(nodes.back( ));
    }

    int i_ = 0;
    for (auto i : *data)
    {//! now bloat for sure
        int j_ = 0;
        for (auto j : *data)
        {
            if (i == j)
            {
                j_++;
                continue;
            }

            bool exists = false;
            for (auto z : nodes[i_]->edgeList)
            {
                if (z->sourceNode( ) == nodes[j_])
                {
                    exists = true;
                    break;
                }
            }
            if (exists)
            {
                j_++;
                continue;
            }

            int points = 0;
            if (nodes[i_]->getLinkedPerson( )->lastname == nodes[j_]->getLinkedPerson( )->lastname)
            {
                points += 2;
            }
            if (nodes[i_]->getLinkedPerson( )->city == nodes[j_]->getLinkedPerson( )->city)
            {
                points += 4;
            }
            if (nodes[i_]->getLinkedPerson( )->street == nodes[j_]->getLinkedPerson( )->street)
            {
                points += 2;
            }
            if (nodes[i_]->getLinkedPerson( )->house_nr == nodes[j_]->getLinkedPerson( )->house_nr)
            {
                points += 2;
            }
            if (nodes[i_]->getLinkedPerson( )->hobby == nodes[j_]->getLinkedPerson( )->hobby)
            {
                points += 4;
            }
            if (nodes[i_]->getLinkedPerson( )->age == nodes[j_]->getLinkedPerson( )->age)
            {
                points += 1;
            }
            if (nodes[i_]->getLinkedPerson( )->workplace == nodes[j_]->getLinkedPerson( )->workplace)
            {
                points += 3;
            }
            for (auto z : nodes[i_]->getLinkedPerson( )->getFriends( ))
            {
                for (auto x : nodes[j_]->getLinkedPerson( )->getFriends( ))
                {
                    if (x == z)
                    {
                        points += 1;
                    }
                }
            }
            if (points > 7)
            {
                scene->addItem(new Edge(nodes[i_], nodes[j_]));
                j_++;
                continue;
            }

            for (auto k : i->getFriends( ))
            {
                if (k->getData( ) == j->getData( ))
                {
                    scene->addItem(new Edge(nodes[i_], nodes[j_]));
                    break;
                }
            }

            j_++;
        }
        i_++;
    }

    QPoint center(0, 0);
    QVector<QPair<int, int>> cor;
    for (int i = 0; i < nodes.size( ); i++)
    {   // setting positions of every node not working quite well
        int xval = QRandomGenerator::global( )->generate( );
        int yval = QRandomGenerator::global( )->generate( );
        int x = (abs(xval) % 5000) - 1000;
        int y = (abs(yval) % 5000) - 1000;
        QPair<int, int> curr;
        bool unique = true;
        int i_ = 0;
        foreach(curr, cor)
        {
            if (!unique)
            {
                break;
            }
            int j_ = 0;
            QPair<int, int> any;
            foreach(any, cor)
            {
                if (i_ == j_)
                {
                    continue;
                }
                if (any == curr)
                {
                    unique = false;
                    break;
                }
                j_++;
            }
            i_++;
        }
        if (!unique)
        {
            i--;
            continue;
        }
        nodes[i]->setPos(x, y);
    }
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

void GraphWidget::findNode( )
{
    qreal x;
    qreal y;

    QStringList str = DialogFind::getStrings(this, nullptr);

    string txt;
    txt.append(str.at(0).toStdString( ));
    txt.append(str.at(1).toStdString( ));

    for (auto i : nodes)
    {
        if (txt == (i->getLinkedPerson( )->firstname + i->getLinkedPerson( )->lastname))
        {
            x = i->x( );
            y = i->y( );
            break;
        }
    }

    // foreach(auto i, nodes)
    // {
    //     i->moveBy(this->rect( ).center( ).x( ) - x, this->rect( ).center( ).y( ) - y);
    // }

    this->fitInView(x - 400, y - 400, 800, 800, Qt::KeepAspectRatio);
}
