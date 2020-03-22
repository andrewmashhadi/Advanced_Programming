#ifndef TROJANSCONTROLLER_H
#define TROJANSCONTROLLER_H

#include <QObject>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QTimer>
#include <QPixmap>
#include <QBrush>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include "Trojan.h"
#include "UCLAPlayer.h"


class TrojansController : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene* game_scene;
    QTimer* releasetrojan_T;
    QTimer* run_animation_T;
    QMediaPlayer* explosion_sound;
    QPixmap* trojan_spritesheet;
    QPixmap* exp_pixmap;
    Sprite* explosion;
    std::vector<QGraphicsSimpleTextItem*> stopwatch;
    QTimer* stopwatch_T;
    double rates_modifier;
    int round_timeleft;
    bool sounds_on;

public:
    /* Constructs the TrojansController object, along with its base class. Sets the game scene, the
       release_time QTimer, and the explosion sound effect. Connects the release_time timer to the
       release slot, so that a Trojan is release everytime the release_time timer goes off.
       @param gs is the game_scene we will add Trojan objects to.
       @param parent is the pointer to the parent object used in the base classes constructor
    */
    explicit TrojansController(QGraphicsScene* gs, QObject *parent = nullptr);

    /* Clears the game_scene and stops the release of Trojans.
       @return void
    */
    void pause();

    /* Starts the release of Trojans at a variable rate depending on the round level.
       @param round_lvl is the round the user is on, determines the speed and rate of the released Trojans
       @return void
    */
    void play(size_t round_lvl);

    /* Function that changes sounds_on boolean value to either true of false depending on if the user has
       clicked the sounds on/off button.
       @param sound is holding the boolean value that sounds_on will be set to
       @return void
    */
    void alter_sound(bool sound);

    /* Destroys this TrojanController object. Clears all objects off the game scene, deletes all of the
       QGraphicsSimpleTextItems in the stopwatch vector, deletes the stop watch timer, deletes the explosion
       spritesheet QPixmap, deletes the trojan_spritesheet QPixmap, deletes the runanimation_T QTimer,
       deletes the releasetrojan_T QTimer, and deletes the explosion sound effect object, exp_sound.
    */
    ~TrojansController();

public slots:
    /* Slot creates a new Trojan object and adds it to the game_scene.
       @return void
    */
    void releasetrojans();

    /* Slot to update the 30-second timer in the top right corner of the game scene.
       @return void.
    */
    void stopwatch_update();

};

#endif // TROJANSCONTROLLER_H
