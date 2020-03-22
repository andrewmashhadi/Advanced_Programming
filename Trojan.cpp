#include "Trojan.h"

Trojan::Trojan(bool sound, QMediaPlayer* e_sound, double rate, QPixmap* ss, Sprite* exp, int w, int h, int nx, int ny, int x_off, int y_off, double scale , int tpf, QObject *parent) :
    QObject(parent),
    Sprite(ss,w,h,nx,ny,x_off,y_off,scale,tpf),
    sounds_on(sound),
    movetrojan_T(new QTimer()),
    explosion_sound(e_sound),
    explosion(exp),
    speed_modifier(1-rate)
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int width = screen_geometry.width();

    int spawn_location = QRandomGenerator::global()->bounded(qRound(0.458*width));
    this->setPos(spawn_location, 0);

    movetrojan_T->start(30*speed_modifier);
    QObject::connect(movetrojan_T, &QTimer::timeout, this, &Trojan::movetrojan_down);

    this->play();
    this->setSequence(0);
}

QPainterPath Trojan::shape() const
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int width = screen_geometry.width();

    QPainterPath path;
    QPolygon polygon;
    polygon << QPoint(this->boundingRect().left()+qRound(0.01*width), this->boundingRect().top());
    polygon << QPoint(this->boundingRect().right()-qRound(0.01*width), this->boundingRect().top());
    polygon << QPoint((this->boundingRect().right())/2, this->boundingRect().bottom());
    polygon << QPoint(this->boundingRect().left()+qRound(0.01*width), this->boundingRect().top());
    path.addPolygon(polygon);

    return path;

}

void Trojan::movetrojan_down()
{
    QList<QGraphicsItem*> items_col = collidingItems();

    // Iterate through the list of colliding items.
    for (QList<QGraphicsItem*>::iterator it = items_col.begin(); it != items_col.end(); ++it)
    {
        Football* t = dynamic_cast<Football*>(*it);
        UCLAPlayer* p = dynamic_cast<UCLAPlayer*>(*it);
        /* If a football hits this Trojan, delete both of the objects. Otherwise if this Trojan
           hits the UCLAPlayer, emit the playertouched signal to change widgets and delete this
           Trojan.
        */
        if (t != nullptr)
        {
            explosion->setPos(this->x(), this->y());
            explosion->play_once();

            // If the user has set the music and sounds to on, play the explosion sound effect.
            if (sounds_on)
            {
                /* If the exp_sound sound effect is still playing, restart it from the beginning.
                   Otherwise, replay() it again.
                */
                if (explosion_sound->state() == QMediaPlayer::PlayingState)
                    explosion_sound->setPosition(0);
                else
                    explosion_sound->play();
            }

            this->scene()->removeItem(*it);
            this->scene()->removeItem(this);
            t->deleteLater();
            this->deleteLater();
            return;
        }
        else if (p != nullptr)
        {
            this->scene()->removeItem(this);
            this->deleteLater();
            emit p->playertouched(true);
            return;
        }
    }

    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();

    this->setPos(this->x(), this->y() + qRound(0.01*height));

    /* If this Trojan object move out of the graphics scene and view, remove it from the scene
       and delete it.
    */
    if (this->y() > 0.64*height)
    {
        scene()->removeItem(this);
        this->deleteLater();
    }
}

Trojan::~Trojan()
{
     movetrojan_T->deleteLater();
}
