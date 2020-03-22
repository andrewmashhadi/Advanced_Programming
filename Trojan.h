#ifndef TROJAN_H
#define TROJAN_H

#include <QObject>
#include <QMediaPlayer>
#include <QTimer>
#include <QPixmap>
#include <QRandomGenerator>
#include <QPainterPath>
#include <QPolygon>
#include "Football.h"
#include "UCLAPlayer.h"
#include "Sprite.h"

class Trojan : public QObject, public Sprite
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

private:
    bool sounds_on;
    QTimer* movetrojan_T;
    QMediaPlayer* explosion_sound;
    Sprite* explosion;
    double speed_modifier;

public:
    /* Constructs this Trojan object, along with its base classes. Create new QTimer object for
       movetrojan_T to point to and sets the exp_sound member variable to also point to the
       QMediaPlayer object containing the explosion sound effect. Randomly chooses an x-location
       from the top of the scene to start running down from. Connects the QTimer member variable
       to the movetrojan_down slot so this object runs down approriately.
       @param sounds_on is true if user wants the explosion sound effect, false if not.
       @param e_sound is the explosion sound effect object that exp_sound will be set to point to
       @param rate will be used to determine how much we modify the speed of the Trojan
       @param ss is the spritesheet
       @param exp is the explosion Sprite
       @param w is the width of a frame.
       @param h is the height of a frame.
       @param nx is the number of frames in x-direction
       @param ny is the number of frames in the y-direction
       @param x_off is the x-location of the upper left corer of the first fram in the spritesheet
       @param y_off is the y-location of the upper left corer of the first fram in the spritesheet
       @param scale is the scaling of the sprite used to help resize the image in an easier way
       @param tpf is the ticks_per_frame used to convenietly adjust the rate of animation
       @param parent is the parent pointer used in QObject classes
    */
    explicit Trojan(bool sounds_on, QMediaPlayer* e_sound, double rate, QPixmap* ss, Sprite* exp, int w, int h, int nx, int ny, int x_off, int y_off, double scale = 1, int tpf=1, QObject* parent = nullptr);

    /* Reshapes the boundary to fit the actual non-transparent image in our sprite sheet.
       @return the QPainterPath that contains the informaion of this new boundary.
    */
    QPainterPath shape() const override;

    /* Destroys this Trojan object. Deletes the QTimer object that movetrojan_T points to.
    */
    ~Trojan();

public slots:
    /* Slot used to move this Trojan object down the screen whenever the QTimer that trojan_speed
       points to goes off. Checks for colliding items that occur in our game's scene, and deletes
       the colliding items objects appropriately.
       @return void
    */
     void movetrojan_down();
};

#endif // TROJAN_H
