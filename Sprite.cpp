#include "Sprite.h"

QRectF Sprite::boundingRect() const
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();
    int width = screen_geometry.width();

    return QRectF(0,0,(_scale*w*width)/1920,(_scale*h*height)/1080);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF sr(x_off + w*cx,y_off + h*cy,w,h);
    painter->drawPixmap(boundingRect(),*ss,sr);
}

void Sprite::advance(int phase)
{
    // If phase is 1 and _animating is true update this animation
    if(phase && _animating)
    {
        ++ticks;
        ticks %= ticks_per_frame;

        // If the ticks_per_frame divided evenly into ticks
        if(ticks == 0)
        {
            ++cx;
            cx %= nx;
            update(boundingRect());
        }
    }

    // This acts as a ticks_per_frame but for animate_once only
    static int a_o_skipper = 0;

    // If phase is 1 and animate_once is true update this animation
    if(phase && animate_once)
    {
        int ticker = (a_o_skipper % 3);
        // If 3 divids a_o_skipper evenly, update the animation
        if (ticker == 0)
        {

            ++cx;
            cx %= nx;
            update(boundingRect());

            //If we have gone through the whole sequence once, set animate_once to false to stop updating.
            if (cx == 0)
            {
                animate_once = false;
            }
        }
        ++a_o_skipper;
    }
}
