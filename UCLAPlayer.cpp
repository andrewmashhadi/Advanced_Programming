#include "UCLAPlayer.h"

UCLAPlayer::UCLAPlayer(QPixmap* ss, int w, int h, int nx, int ny, int x_off, int y_off, double scale, int tpf, QObject* parent):
    QObject(parent),
    Sprite(ss, w, h, nx, ny, x_off, y_off, scale, tpf),
    throwing_sound(new QMediaPlayer()),
    run_T(new QTimer()),
    direction(0),
    running(false),
    sounds_on(true)
{
    throwing_sound->setMedia(QUrl("qrc:/music/throw.mp3"));

    QObject::connect(run_T, &QTimer::timeout, this, &UCLAPlayer::move);
    run_T->start(1000/50);
}

void UCLAPlayer::run(int dir)
{
    direction = dir;
    running = true;
}

void UCLAPlayer::stop_running()
{
    running = false;
    this->pause();
}

void UCLAPlayer::alter_sound(bool sound)
{
    sounds_on = sound;
}

QPainterPath UCLAPlayer::shape() const
{
    QPainterPath path;
    path.arcMoveTo(this->boundingRect(), 225);
    path.arcTo(this->boundingRect(), 225, 90);
    path.lineTo(QPoint((1/2)*(this->boundingRect().right()), (1/2)*(this->boundingRect().bottom())));
    path.arcTo(this->boundingRect(), 45, 90);
    path.lineTo(QPoint((1/2)*(this->boundingRect().right()), (1/2)*(this->boundingRect().bottom())));
    path.closeSubpath();

    return path;
}

void UCLAPlayer::move()
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int width = screen_geometry.width();

    int onestep_X = qRound(0.01*width);

    // If running was set to true, move this UCLAPlayer one step in the appropriate direction
    if (running)
    {
        /* If the direction is set to 0 and we have space to move to the left, move one step to
          the left. Otherwise if the direction is set to 1 and we have space to move to the right,
          move one step to the right.
        */
        if (direction == 0 && this->x() >= 0)
        {
           this->play();
           this->setPos(this->x()-onestep_X, this->y());
        }
        else if (direction == 1 && this->x() < qRound(0.455*width))
        {
            this->play();
            this->setPos(this->x()+onestep_X, this->y());
        }
    }
}

 UCLAPlayer::~UCLAPlayer()
 {
     throwing_sound->deleteLater();
     run_T->deleteLater();
 }
