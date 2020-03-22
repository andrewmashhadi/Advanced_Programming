#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QTimer>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>

class Football : public QGraphicsObject
{
    Q_OBJECT

private:
     QTimer* movefootball_T;

public:
     /* Constructs Football class, calls its base class's default constructor. Creates timer for
        movefootball_T and connects its corresponding timeout signal with a movement slot.
     */
    Football();

    /* Overrides the QGraphicsItem paint function to paint the football.
       @param painter is a Qpainter pointer used in QGraphicsItem's orginal paint member function
       @param option is a QStyleOptionGraphicsItem pointer used in QGraphicsItem's orginal paint member function
       @param widget is a QWidget pointer used in QGraphicsItem's orginal paint member function
       @return void
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /* Overrides the QGraphcisItem function to set the rectangular bound around this football.
       @return void
    */
    QRectF boundingRect() const override;

    /* Destroys this Football object. Deletes this object's QTimer object.
       @return void
    */
    ~Football();

public slots:
    /* This slot is used to move the position of the football up the screen once fb_speed's timeout signal
       is emitted.
       @return void
    */
    void move_football();
};

#endif // FOOTBALL_H
