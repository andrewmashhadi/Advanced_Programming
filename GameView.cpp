#include "GameView.h"

GameView::GameView():QGraphicsView(), ucla_player(nullptr) {}

void GameView::setPlayer(UCLAPlayer* p)
{
    ucla_player = p;
}

void GameView::keyPressEvent(QKeyEvent *ev)
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();
    int width = screen_geometry.width();

    // If the left arrow key was pressed, move this ucla_player to the left by 15 pxls.
    if (ev->key() == Qt::Key_Left)
    {
       ucla_player->setSequence(0);
       ucla_player->run(0);
    }
    // Otherwise if the right arrow key was pressed, move the ucla_player to the right by 15 pxls.
    else if (ev->key() == Qt::Key_Right)
    {
        ucla_player->setSequence(1);
        ucla_player->run(1);

    }
    // Otherwise if the up arrow key was pressed, create a football and set its position to the center of this object.
    else if (ev->key() == Qt::Key_Up)
    {
        ucla_player->setSequence(2);
        ucla_player->play_once();

        // If the user has set the music and sounds to on, proceed with the throwing sound effect.
        if (ucla_player->sounds_on)
        {
            /* If ucla_player's throwing_sound sound effect is still playing. Restart it from the beginning.
               Otherwise, just play the sound effect over again.
            */
            if (ucla_player->throwing_sound->state() == QMediaPlayer::PlayingState)
                ucla_player->throwing_sound->setPosition(100);
            else
            {
                ucla_player->throwing_sound->setPosition(100);
                ucla_player->throwing_sound->play();
            }
        }
        Football* fb = new Football();
        this->scene()->addItem(fb);
        fb->setPos(ucla_player->x()+qRound(0.0082*width), ucla_player->y()-qRound(0.017*height));
    }
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
       ucla_player->stop_running();
    else if (event->key() == Qt::Key_Right)
       ucla_player->stop_running();
}
