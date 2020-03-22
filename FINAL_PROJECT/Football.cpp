#include "Football.h"

Football::Football():QGraphicsObject(), movefootball_T(new QTimer())
{
    QObject::connect(movefootball_T, &QTimer::timeout, this, &Football::move_football);
    movefootball_T->start(20);
}

void Football::paint(QPainter *painter, const QStyleOptionGraphicsItem* , QWidget* )
{
    painter->setBrush(Qt::darkRed);
    painter->drawEllipse(boundingRect());
}

QRectF Football::boundingRect() const
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();
    int width = screen_geometry.width();

    return QRectF(0,0, qRound(0.010*width), qRound(0.03*height));
}

void Football::move_football()
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();

    this->setPos(this->x(), this->y()-qRound(0.018*height));

    // If this entire football is out of the fixed view and scene window, delete this football.
    if (this->y() < -qRound(0.030*height))
    {
        this->scene()->removeItem(this);
        this->deleteLater();
    }
}

Football::~Football()
{
    movefootball_T->deleteLater();
}
