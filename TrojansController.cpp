 #include "TrojansController.h"

TrojansController::TrojansController(QGraphicsScene* gs, QObject *parent) :
    QObject(parent),
    game_scene(gs),
    releasetrojan_T(new QTimer()),
    run_animation_T(new QTimer()),
    explosion_sound(new QMediaPlayer()),
    trojan_spritesheet(new QPixmap(":/images/trojansprite.png")),
    exp_pixmap(new QPixmap(":/images/expsprite.png")),
    explosion(nullptr),
    stopwatch(),
    stopwatch_T(new QTimer()),
    rates_modifier(0),
    round_timeleft(30),
    sounds_on(true)
{
    explosion_sound->setMedia(QUrl("qrc:/music/explosion.mp3"));

    QObject::connect(releasetrojan_T, &QTimer::timeout, this, &TrojansController::releasetrojans);

    // This run_animation calls advance on the game_scene, so it will advance the UCLAPlayer also
    run_animation_T->start(1000/60);
    QObject::connect(run_animation_T, &QTimer::timeout, game_scene, &QGraphicsScene::advance);

    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();
    int width = screen_geometry.width();

    QFont swfont("Impact");
    swfont.setPixelSize(qRound(0.03*height));

    /* For loop to store 30 QString elements of our 30-second timer vector used to display
       time left in the current round.
    */
    for (size_t i = 0; i < 30; ++i)
    {
        stopwatch.push_back(new QGraphicsSimpleTextItem());
        game_scene->addItem(stopwatch[i]);
        stopwatch[i]->setFont(swfont);

        // If we are filling the first 10 elements, we want the Qstrings to be red.
        if (i < 10)
            stopwatch[i]->setBrush(QBrush(Qt::red));

        stopwatch[i]->setText(QString::number(i+1) + QString::fromStdString(" seconds"));
        stopwatch[i]->setPos(qRound(0.43*width), qRound(0.008*height));

        // Make every element of the stopwatch vector invisible in our game scene, except the last.
        if (i != 29)
            stopwatch[i]->setVisible(false);
    }

    QObject::connect(stopwatch_T, &QTimer::timeout, this, &TrojansController::stopwatch_update);
}

void TrojansController::pause()
{
    // If stopwatch_T timer is currently running, stop it from going off.
    if(stopwatch_T->isActive())
        stopwatch_T->stop();

    round_timeleft = 30;

    // Since pause was called, we make every element of the stopwatch vector invisible in our game scene, except the last.
    for (size_t i = 0; i < 30; ++i)
    {
        // If the i is not at 29, set the ith element to be not visibale. Otherwise, set it to be visable.
        if (i != 29)
            stopwatch[i]->setVisible(false);
        else
            stopwatch[i]->setVisible(true);
    }
    QList<QGraphicsItem*> allitems = game_scene->items();
    // Iterate through all the items in the scene. Delete all items except the UCLAPlayer and QGraphicsSimpleTextItems.
    for (QList<QGraphicsItem*>::Iterator it = allitems.begin(); it != allitems.end(); ++it)
    {
        UCLAPlayer* p = dynamic_cast<UCLAPlayer*>(*it);
        QGraphicsSimpleTextItem* st = dynamic_cast<QGraphicsSimpleTextItem*>(*it);
        // If the current QGraphicsItem pointer is not a UCLAPlayer or QGraphicsSimpleTextItem pointer, remove and delete it.
        if (p == nullptr && st == nullptr)
        {
            game_scene->removeItem(*it);
            delete *it;
        }
    }
    // If releasetrojan_T timer is currently running, stop it from going off.
    if(releasetrojan_T->isActive())
        releasetrojan_T->stop();
}

void TrojansController::play(size_t round_lvl)
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();

    explosion = new Sprite(exp_pixmap, 240, 228, 4, 1, 0, 0, 0.5);      // Gets deleted in pause() after round ends
    game_scene->addItem(explosion);
    explosion->setPos(0, -qRound(0.28*height));  // Hides the explosion when first added to scene

    stopwatch_T->start(1000);

    // If the current round is under 10, it sets the rates_modifier to be 4% of the current round.
    if(round_lvl < 10)
        rates_modifier = round_lvl*0.04;

    releasetrojan_T->start(1000*(1-2*rates_modifier));
}

void TrojansController::alter_sound(bool sound)
{
    sounds_on = sound;
}

void TrojansController::releasetrojans()
{
    Trojan* one_trojan= new Trojan(sounds_on, explosion_sound, rates_modifier, trojan_spritesheet, explosion, 275, 300, 2, 1, 5, 10, 0.48, 20*(1-rates_modifier));
    game_scene->addItem(one_trojan);
}

void TrojansController::stopwatch_update()
{
    --round_timeleft;
    // If there is more time left in the round, make the next second visable while making the previous second invisible.
    if (round_timeleft > 0)
    {
        stopwatch[round_timeleft]->setVisible(false);
        stopwatch[round_timeleft-1]->setVisible(true);
    }
}

TrojansController::~TrojansController()
{
    releasetrojan_T->deleteLater();
    explosion_sound->deleteLater();
    run_animation_T->deleteLater();
    // Go through all the QGraphicsSimpleTextItem's in the game scene and remove them. Then delete them.
    for (size_t i = 0; i < 30; i++)
    {
        game_scene->removeItem(stopwatch[i]);
        delete stopwatch[i];
        stopwatch[i] = nullptr;
    }
    stopwatch_T->deleteLater();
    delete exp_pixmap;
    delete trojan_spritesheet;
}
