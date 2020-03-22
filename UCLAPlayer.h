#ifndef UCLAPLAYER_H
#define UCLAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>
#include <QTimer>
#include <QPainterPath>
#include "Sprite.h"
#include "Football.h"

class UCLAPlayer : public QObject, public Sprite
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

private:
    QMediaPlayer* throwing_sound;
    QTimer* run_T;
    int direction;
    bool running;
    bool sounds_on;

public:
    /* Constructs this UCLAPlayer object and its base class portions.
       @param ss is the spritesheet
       @param w is the width of a frame.
       @param he is the height of a frame.
       @param nx is the number of frames in x-direction
       @param ny is the number of frames in the y-direction
       @param x_off is the x-location of the upper left corer of the first fram in the spritesheet
       @param y_off is the y-location of the upper left corer of the first fram in the spritesheet
       @param scale is the scaling of the sprite used to help resize the image in an easier way
       @param tpf is the ticks_per_frame used to convenietly adjust the rate of animation
       @param parent is the parameter used to deteremine the parent of this QObject
    */
    explicit UCLAPlayer(QPixmap* ss, int w, int h, int nx, int ny, int x_off, int y_off, double scale = 1, int tpf=1, QObject* parent = nullptr);

    /* Sets the direction of the UCLAPlayer to the direction corresponding to the int parameter dir
       and then sets running to true to allow the run_T timer and the move slot to move this UCLAPlayer.
       @param dir is an integer corresponding to the direction the ucla player needs to move
       @return void
    */
    void run(int dir);

    /* Sets running to false to prevent the run_T timer and the move slot from moving this UCLAPlayer.
       Then it pauses the animation of this Sprite object.
       @return void.
    */
    void stop_running();

    /* Function that changes sounds_on boolean value to either true of false depending on if the user has
       clicked the sounds on/off button.
       @param sound is holding the boolean value that sounds_on will be set to
       @return void
    */
    void alter_sound(bool sound);

    /* Reshapes the boundary to fit the actual non-transparent image in our sprite sheet.
       @return the QPainterPath that contains the informaion of this new boundary.
    */
    QPainterPath shape() const override;

    /* Destroys this UCLAPlayer object and deletes the throwing_sound QMediaPlayer and
       run_T QTimer.
    */
    ~UCLAPlayer();

signals:
    /* Signal is emitted at the end of the round if never touched or emitted when touched.
       @param boolean holds value stores true if touched and false otherwise
    */
    void playertouched(bool);

public slots:
    /* This slot starts the animation and moves this UCLAPlayer left or right depending on the value
       of dir. It takes one step in that direction if running is set to true.
       @return void.
    */
    void move();

    friend class GameView;
};

#endif // UCLAPLAYER_H
