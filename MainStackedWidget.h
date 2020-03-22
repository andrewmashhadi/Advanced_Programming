#ifndef MAINSTACKEDWIDGET_H
#define MAINSTACKEDWIDGET_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QString>
#include <QMediaPlayer>
#include <QTimer>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>
#include "TrojansController.h"
#include "GameView.h"
#include "UCLAPlayer.h"

class MainStackedWidget : public QStackedWidget
{
    Q_OBJECT

private:
    size_t round_number;
    size_t sounds_counter;
    bool survived_round;
    bool sounds_on;
    QPushButton* game_b;
    QPushButton* rules_b;
    QPushButton* rulestomain_b;
    QPushButton* resultstomain_b;
    QPushButton* resultstogame_b;
    QPushButton* mute_b;
    QPushButton* quit_b;
    QLabel* gametitle_t;
    QLabel* roundcomplete_t;
    QLabel* rules_t;
    QLabel* lostround_t;
    QLabel* rules_txt;
    QLabel* keys_picture_t;
    QWidget* game_w;
    QWidget* roundcomplete_w;
    QWidget* rules_w;
    QWidget* main_w;
    QWidget* rulestext_w;
    QWidget* lostround_w;
    QWidget* win_star_w;
    QWidget* over_w;
    QWidget* title_w;
    QVBoxLayout* main_l;
    QHBoxLayout* game_l;
    QHBoxLayout* star_centering_l;
    QHBoxLayout* over_l;
    QHBoxLayout* r_to_g_button_l;
    QHBoxLayout* r_to_m_button_l;
    QHBoxLayout* wintext_l;
    QHBoxLayout* losetext_l;
    QHBoxLayout* title_l;
    QHBoxLayout* gb_l;
    QHBoxLayout* rb_l;
    QHBoxLayout* mb_l;
    QHBoxLayout* qb_l;
    QHBoxLayout* rules_pic_l;
    QHBoxLayout* rt_l;
    QVBoxLayout* rules_txt_l;
    QVBoxLayout* text_l;
    QVBoxLayout* rules_l;
    QVBoxLayout* results_l;
    QVBoxLayout* roundcomplete_l;
    QGraphicsScene* game_scene;
    GameView* game_view;
    QMediaPlayer* main_m;
    QMediaPlayer* game_m;
    QMediaPlayer* roundcomplete_m;
    QMediaPlayer* lostround_m;
    QTimer* roundcomplete_T;
    QTimer* music_transition_T;
    TrojansController* trojan_controller;
    QPixmap* ucla_sprite;
    UCLAPlayer* ucla_player;

public:
    /* Constructor with parameter for this MainStackedWidget.
       @param qb is pointing to the exit button that will be located on the welcome window
    */
    MainStackedWidget(QPushButton* qb);

    /* Destructs this MainStackedWidget object, and deletes the private member objects that do not already
       have Qt style owners that delallocate their memory for them.
    */
    ~MainStackedWidget();

signals:
    /* Signal that is emitted to change the current widget of this MainStackedWidget object to what w points to.
       @param w is a pointer to the widget that we want to have shown on top.
       @return void
    */
     void switchto(QWidget* w);

public slots:
     /* Slot that is connected to the "Go Back" buttons in the rules and lostround windows that emits
        the switchto signal so we can set the current widget back to the welcome window.
        @return void
     */
     void changedtomain();

     /* Slot that is connected to the "Play Game" and the "next round" buttons in the welcome
        and the roundcomplete windows that emits the switchto signal so we can set the current
        widget to the widget containing the game and graphics scene.
        @return void
     */
     void changedtogame();

     /* Slot that is connected to the "Rules" button in the welcome window that emits the switchto signal
        so we can set the current widget to the rules window.
        @return void
     */
     void changedtorules();

     /* Stops and clears all Trojans being released, switches music, plays a round ending sound,
        and changes to the window corresponding to if they completed the round.
        @param touched is a boolean variable used to tell if the round was won or lost.
        @return void
     */
     void changedtoresults(bool touched);

     /* Used when roundcomplete_T timer goes off for the end off round. Emits signal meant
        to connect with the changetoresults slot that passes a true value.
        @return void
     */
     void roundinfo();

     /* Used to turn all music and sounds off or back on. This slot should be connected with
        the sounds on/off button.
        @return void
     */
     void soundcontrol();
};

#endif // MAINSTACKEDWIDGET_H
