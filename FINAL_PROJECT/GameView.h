#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>
#include "UCLAPlayer.h"
#include "Trojan.h"

class GameView : public QGraphicsView
{
private:
    UCLAPlayer* ucla_player;

public:
    /* Constructor for this GameView class. Calls base class default contructor and initiallizes
       ucla_player to nullptr.
    */
    GameView();

    /* Sets the ucla_player pointer to point to the ucla_player added to the QGraphicsScene corresponding
       to this GameView.
       @return void
    */
    void setPlayer(UCLAPlayer* p);

protected:
    /* Called when the user hits a key on the keyboard.
       @param ev is the QKeyEvent carrying the information about the key that was pressed
       @return void
    */
    void keyPressEvent(QKeyEvent *ev) override;

    /* Called when the user releases a key on the keyboard.
       @param event is the QKeyEvent carrying the information about the key that was released
       @return void
    */
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // GAMEVIEW_H
