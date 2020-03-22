#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QTimer>
#include <QPainter>
#include <QGuiApplication>
#include <QtGlobal>
#include <QScreen>

class Sprite : public QGraphicsItem
{
private:
    QPixmap* ss; // spritesheet
    int w, h; // width/height of a single frame
    int nx, ny; // number of frames in the x/y direction
    int cx, cy; // current frame position
    int x_off, y_off; // location of upper left corner of first frame in the spritesheet
    double _scale; // scale of the sprite
    int ticks_per_frame;
    int ticks;
    bool _animating;
    bool animate_once;


public:
    /* Inline constructor with parameters for this Sprite class. Sets up all the member fields correctly.
       @param ss_ is the spritesheet
       @param wi is the width of a frame.
       @param he is the height of a frame.
       @param nx_ is the number of frames in x-direction
       @param ny_ is the number of frames in the y-direction
       @param x_off_ is the x-location of the upper left corer of the first fram in the spritesheet
       @param y_off_ is the y-location of the upper left corer of the first fram in the spritesheet
       @param scale is the scaling of the sprite used to help resize the image in an easier way
       @param tpf is the ticks_per_frame used to convenietly adjust the rate of animation
    */
    Sprite(QPixmap* ss_, int wi, int he, int nx_, int ny_, int x_off_, int y_off_, double scale = 1, int tpf=1): ss(ss_),
        w(wi), h(he), nx(nx_), ny(ny_), cx(0), cy(0), x_off(x_off_), y_off(y_off_), _scale(scale), ticks_per_frame(tpf),
        ticks(0),_animating(false), animate_once(false) {}


    /* Sets and returns the rectangle bounding this QGraphicsItem.
       @return the QRect that is the rectangle bounding this QGraphicsItem
    */
    QRectF boundingRect() const override;

    /* Overrides the QGraphicsItem paint function to paint this animation.
       @param painter is a Qpainter pointer used in QGraphicsItem's orginal paint member function
       @param option is a QStyleOptionGraphicsItem pointer used in QGraphicsItem's orginal paint member function
       @param widget is a QWidget pointer used in QGraphicsItem's orginal paint member function
       @return void
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /* Overrides the QGraphicsItem advance function to advance the animation when called.
       @param phase is 0 to indicate that items are about to advance, then 1 when ready to advance
       @return void
    */
    void advance(int phase) override;

    /* Sets the scale of the animation.
       @param s is the new scaling factor we want to change to.
       @return void
    */
    void setScale(double s)
    {
        _scale = s;
    }

    /* Gets the scaling value of the aimation.
       @return the scaling factor.
    */
    double scale() const
    {
        return _scale;
    }

    /* Returns the sequence of the sprite sheet we are currently on.
       @return the sequence of the spritesheet we are currently on.
    */
    int sequence() const
    {
        return cy;
    }

    /* Sets the sequence of the sprite sheet we want to be on.
       @return void.
    */
    void setSequence(int seq_num)
    {
        cy = (seq_num % ny);
    }

    /* Returns the boolean value indicating if this Sprite object is currently animating.
       @return a copy of _animating, containing the boolean value indicating if this is currently animating
    */
    bool animating() const
    {
        return _animating;
    }

    /* Sets this Sprite object's animating to the parameter a.
       @param a is the boolean value conataing true if we want to begin animating and false otherwise
       @return void
    */
    void setAnimating(bool a)
    {
        _animating = a;
    }

    /* Pause calls setAnimating with input false to stop animating this Sprite object.
       @return void
    */
    void pause()
    {
        setAnimating(false);
    }

    /* Play calls setAnimating with input true to begin animating this Sprite object.
       @return void
    */
    void play()
    {
        setAnimating(true);
    }

    /* Play sets animate_once true to animate through the current sequence once for this Sprite
       object. Sets play to false so it doesnt continue to animate after on accident.
       @return void
    */
    void play_once()
    {
        animate_once = true;
        _animating = false;
    }

    /* Resets the animation to the first frame of the current sequence in  our Spritesheet.
       @return void
    */
    void resetAnimation()
    {
        cx=0;
    }

    /* Default destructor for Sprite object.
    */
    virtual ~Sprite() {}

};

#endif // SPRITE_H
