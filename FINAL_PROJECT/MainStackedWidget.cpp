#include "MainStackedWidget.h"

MainStackedWidget::MainStackedWidget(QPushButton* qb):
    QStackedWidget(),
    round_number(1),
    sounds_counter(1),
    survived_round(false),
    sounds_on(true),
    game_b(new QPushButton("Play Game")),
    rules_b(new QPushButton("Rules")),
    rulestomain_b(new QPushButton("Back")),
    resultstomain_b(new QPushButton("Back to Main Menu")),
    resultstogame_b(new QPushButton("Next Round")),
    mute_b(new QPushButton("Sound On/Off")),
    quit_b(qb),
    gametitle_t(new QLabel("Angry Trojans!")),
    roundcomplete_t(new QLabel()),
    rules_t(new QLabel("Rules of the Game")),
    lostround_t(new QLabel("You have lost!")),
    rules_txt(new QLabel()),
    keys_picture_t(new QLabel()),
    game_w(new QWidget()),
    roundcomplete_w(new QWidget()),
    rules_w(new QWidget()),
    main_w(new QWidget()),
    rulestext_w(new QWidget()),
    lostround_w(new QWidget()),
    win_star_w(new QWidget()),
    over_w(new QWidget()),
    title_w(new QWidget()),
    main_l(new QVBoxLayout()),
    game_l(new QHBoxLayout()),
    star_centering_l(new QHBoxLayout()),
    over_l(new QHBoxLayout()),
    r_to_g_button_l(new QHBoxLayout()),
    r_to_m_button_l(new QHBoxLayout()),
    wintext_l(new QHBoxLayout()),
    losetext_l(new QHBoxLayout()),
    title_l(new QHBoxLayout()),
    gb_l(new QHBoxLayout()),
    rb_l(new QHBoxLayout()),
    mb_l(new QHBoxLayout()),
    qb_l(new QHBoxLayout()),
    rules_pic_l(new QHBoxLayout()),
    rt_l(new QHBoxLayout()),
    rules_txt_l(new QVBoxLayout()),
    text_l(new QVBoxLayout()),
    rules_l(new QVBoxLayout()),
    results_l(new QVBoxLayout()),
    roundcomplete_l(new QVBoxLayout()),
    game_scene(new QGraphicsScene()),
    game_view(new GameView()),
    main_m(new QMediaPlayer()),
    game_m(new QMediaPlayer()),
    roundcomplete_m(new QMediaPlayer()),
    lostround_m(new QMediaPlayer()),
    roundcomplete_T(new QTimer()),
    music_transition_T(new QTimer()),
    trojan_controller(nullptr),
    ucla_sprite(new QPixmap(":/images/Ucla_player_sprite.png")),
    ucla_player(new UCLAPlayer(ucla_sprite, 170, 225, 4, 3, 18, 10, 0.82, 2))
{
    // Get information about computer's screen size
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screen_geometry = screen->availableGeometry();
    int height = screen_geometry.height();
    int width = screen_geometry.width();

    game_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    game_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap bg_image(":/images/game_background.PNG");
    bg_image = bg_image.scaled(QSize(qRound(0.54*width), qRound(0.74*height)));
    game_view->setBackgroundBrush(QBrush(bg_image));

    game_scene->setSceneRect(0, 0, qRound(0.5208*width), qRound(0.67*height));

    ucla_player->setFlag(QGraphicsItem::ItemIsFocusable);
    ucla_player->setFocus();
    ucla_player->setPos(qRound(0.26*width), qRound(0.49*height));

    game_scene->addItem(ucla_player);

    game_view->setPlayer(ucla_player);
    game_view->setScene(game_scene);
    game_view->setFixedSize(qRound(0.5208*width), qRound(0.67*height));

    game_l->addWidget(game_view);
    game_l->setAlignment(Qt::AlignCenter);
    game_w->setLayout(game_l);

    trojan_controller = new TrojansController(game_scene);

    int m_titletoscreen = qRound(0.085*width);
    gametitle_t->setStyleSheet("QLabel { color: black; font:" + QString::number(m_titletoscreen) + "px  'impact';}");

    game_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    int buttontoscreen = qRound(0.0156*width);
    game_b->setStyleSheet("background-color: gold; color: black; font: " + QString::number(buttontoscreen) + "px 'impact';");

    rules_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    rules_b->setStyleSheet("background-color: gold; color: black; font: " + QString::number(buttontoscreen) + "px  'impact';");

    mute_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    mute_b->setStyleSheet("background-color: gold; color: black; font: " + QString::number(buttontoscreen) + "px 'impact';");

    quit_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    quit_b->setStyleSheet("background-color: gold; color: black; font: " + QString::number(buttontoscreen) + "px  'impact';");

    int rtm_buttontoscreen = qRound(0.013*width);
    rulestomain_b->setStyleSheet("background-color: gold; color: black; font: "+ QString::number(rtm_buttontoscreen) + "px  'impact';");
    rulestomain_b->setFixedSize(qRound(0.18*width), qRound(0.04*height));

    int rulestoscreen = qRound(0.026*width);
    rules_t->setStyleSheet("QLabel { background-color: gold; color: black; font: "+ QString::number(rulestoscreen) + "px  'impact';}");
    rules_t->setFixedSize(qRound(0.195*width), qRound(0.06*height));
    text_l->setAlignment(Qt::AlignTop);

    rules_txt->setText("Angry USC football players charge towards you from the top of the\n"
                       "screen. You, a UCLA student, are at the bottom of the screen. Your\n"
                       "objective is to dodge or destroy them! Use the right and left arrow\n"
                       "keys to move and dodge enemies, and use the up arrow key to throw\n"
                       "footballs to defend yourself from angry trojans! If an enemy touches\n"
                       "you, you automatically lose and gameplay ends. To win, you must\n"
                       "survive 10 rounds. Each round is approximately 30 seconds. However,\n"
                       "the trojans get angrier with our success, so you'll be faced with\n"
                       "more of them in each round and they'll come running even faster!");

    rt_l->setAlignment(Qt::AlignCenter);
    rt_l->addWidget(rules_txt);

    QPixmap keys_picture(":/images/keyboard_img.png");
    keys_picture_t->setPixmap(keys_picture);
    keys_picture_t->setFixedSize(qRound(0.35*width), qRound(0.26*height));
    keys_picture_t->setScaledContents(true);
    keys_picture_t->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored);

    rules_pic_l->setAlignment(Qt::AlignCenter);
    rules_pic_l->addWidget(keys_picture_t);

    rules_txt->setStyleSheet("QLabel { color: black; font: "+ QString::number(qRound(0.0142*width)) + "px  'ariel';}");
    rules_txt_l->addLayout(rt_l);
    rules_txt_l->addLayout(rules_pic_l);
    text_l->addLayout(rules_txt_l);

    rulestext_w->setFixedSize(qRound(0.50*width), qRound(0.6*height));
    rulestext_w->setLayout(text_l);
    rulestext_w->setStyleSheet("background-color: gold;");

    rules_l->setAlignment(Qt::AlignCenter);
    rules_l->addWidget(rules_t);
    rules_l->addWidget(rulestext_w);
    rules_l->addWidget(rulestomain_b);

    rules_w->setLayout(rules_l);
    QPixmap rules_bkgnd(":/images/main_bg.png");
    rules_bkgnd = rules_bkgnd.scaled(QSize(qRound(0.54*width), qRound(0.74*height)), Qt::IgnoreAspectRatio);
    QPalette rules_palette;
    rules_palette.setBrush(QPalette::Background, rules_bkgnd);
    rules_w->setAutoFillBackground(true);
    rules_w->setPalette(rules_palette);

    int losttoscreen = qRound(0.08*width);
    lostround_t->setStyleSheet("QLabel {color: gold; font: "+ QString::number(losttoscreen) + "px  'impact';}");
    losetext_l->addWidget(lostround_t);
    losetext_l->setAlignment(Qt::AlignCenter);

    resultstomain_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    resultstomain_b->setStyleSheet("background-color: gold; color: black; font: "+ QString::number(buttontoscreen) + "px  'impact';");
    r_to_m_button_l->addWidget(resultstomain_b);
    r_to_m_button_l->setAlignment(Qt::AlignCenter);

    QPixmap over_bkgnd(":/images/game_over.png");
    over_bkgnd = over_bkgnd.scaled(QSize(qRound(0.25*width), qRound(0.33*height)),Qt::IgnoreAspectRatio);
    QPalette over_palette;
    over_palette.setBrush(QPalette::Background, over_bkgnd);
    over_w->setFixedSize(qRound(0.25*width), qRound(0.33*height));
    over_w->setAutoFillBackground(true);
    over_w->setPalette(over_palette);
    over_l->addWidget(over_w);
    over_l->setAlignment(Qt::AlignCenter);

    results_l->addLayout(losetext_l);
    results_l->addLayout(over_l);
    results_l->addLayout(r_to_m_button_l);

    lostround_w->setLayout(results_l);

    int wintoscreen = qRound(0.042*width);
    roundcomplete_t->setStyleSheet("QLabel { color: gold; font: "+ QString::number(wintoscreen) + "px  'impact';}");
    wintext_l->addWidget(roundcomplete_t);
    wintext_l->setAlignment(Qt::AlignCenter);

    resultstogame_b->setStyleSheet("background-color: gold; color: black; font: "+ QString::number(buttontoscreen) + "px 'impact';");
    resultstogame_b->setFixedSize(qRound(0.26*width), qRound(0.04*height));
    r_to_g_button_l->addWidget(resultstogame_b);
    r_to_g_button_l->setAlignment(Qt::AlignCenter);

    QPixmap star_bkgnd(":/images/win_star.png");
    star_bkgnd = star_bkgnd.scaled(QSize(qRound(0.3*width), qRound(0.42*height)),Qt::IgnoreAspectRatio);
    QPalette star_palette;
    star_palette.setBrush(QPalette::Background, star_bkgnd);
    win_star_w->setFixedSize(qRound(0.3*width), qRound(0.42*height));
    win_star_w->setAutoFillBackground(true);
    win_star_w->setPalette(star_palette);
    star_centering_l->addWidget(win_star_w);
    star_centering_l->setAlignment(Qt::AlignCenter);

    roundcomplete_l->addLayout(wintext_l);
    roundcomplete_l->addLayout(star_centering_l);
    roundcomplete_l->addLayout(r_to_g_button_l);
    roundcomplete_w->setLayout(roundcomplete_l);

    title_l->addWidget(gametitle_t);
    title_l->setAlignment(Qt::AlignCenter);
    title_w->setFixedSize(qRound(0.52*width), qRound(0.20*height));
    title_w->setLayout(title_l);
    title_w->setStyleSheet("background-color: gold;");

    gb_l->addWidget(game_b);
    gb_l->setAlignment(Qt::AlignCenter);

    rb_l->addWidget(rules_b);
    rb_l->setAlignment(Qt::AlignCenter);

    mb_l->addWidget(mute_b);
    mb_l->setAlignment(Qt::AlignCenter);

    qb_l->addWidget(quit_b);
    qb_l->setAlignment(Qt::AlignCenter);

    main_l->setAlignment(Qt::AlignCenter);
    main_l->addWidget(title_w);
    main_l->addLayout(gb_l);
    main_l->addLayout(rb_l);
    main_l->addLayout(mb_l);
    main_l->addLayout(qb_l);
    main_w->setLayout(main_l);

    QPixmap main_bkgnd(":/images/main_bg.png");
    main_bkgnd = main_bkgnd.scaled(QSize(qRound(0.54*width), qRound(0.74*height)),Qt::IgnoreAspectRatio);
    QPalette main_palette;
    main_palette.setBrush(QPalette::Background, main_bkgnd);
    main_w->setAutoFillBackground(true);
    main_w->setPalette(main_palette);

    this->addWidget(main_w);
    this->addWidget(game_w);
    this->addWidget(rules_w);
    this->addWidget(lostround_w);
    this->addWidget(roundcomplete_w);
    this->setWindowTitle("Angry Trojans!");
    this->setFixedSize(qRound(0.54*width), qRound(0.74*height));

    QPixmap sw_bkgnd(":/images/bg_red.PNG");
    sw_bkgnd = sw_bkgnd.scaled(QSize(qRound(0.54*width), qRound(0.74*height)),Qt::IgnoreAspectRatio);
    QPalette sw_palette;
    sw_palette.setBrush(QPalette::Background, sw_bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(sw_palette);

    QObject::connect(game_b, &QPushButton::pressed, this, &MainStackedWidget::changedtogame);
    QObject::connect(rules_b, &QPushButton::pressed, this, &MainStackedWidget::changedtorules);
    QObject::connect(mute_b, &QPushButton::pressed, this, &MainStackedWidget::soundcontrol);
    QObject::connect(rulestomain_b, &QPushButton::pressed, this, &MainStackedWidget::changedtomain);
    QObject::connect(ucla_player, &UCLAPlayer::playertouched, this, &MainStackedWidget::changedtoresults);
    QObject::connect(resultstomain_b, &QPushButton::pressed, this, &MainStackedWidget::changedtomain);
    QObject::connect(resultstogame_b, &QPushButton::pressed, this, &MainStackedWidget::changedtogame);
    QObject::connect(roundcomplete_T, &QTimer::timeout, this, &MainStackedWidget::roundinfo);
    QObject::connect(this, &MainStackedWidget::switchto, this, &QStackedWidget::setCurrentWidget);

    game_m->setMedia(QUrl("qrc:/music/Planet_Zebes.mp3"));
    main_m->setMedia(QUrl("qrc:/music/Yoshi's_Island.mp3"));
    roundcomplete_m->setMedia(QUrl("qrc:/music/Stage_Clear.mp3"));
    lostround_m->setMedia(QUrl("qrc:/music/round_lost.mp3"));
    main_m->play();

    // Used a single-shot timer to not have main music start during the win or lose sound effect
    music_transition_T->setInterval(2500);
    music_transition_T->setSingleShot(true);
    QObject::connect(music_transition_T, &QTimer::timeout, main_m, &QMediaPlayer::play);
}

void MainStackedWidget::changedtomain()
{
    emit switchto(main_w);
}

void MainStackedWidget::changedtogame()
{
    roundcomplete_T->start(30000);
    trojan_controller->play(round_number);

    // If the music_transition timer is still active, prevent it from playing main music now.
    if (music_transition_T->isActive())
    {
        music_transition_T->stop();
    }

    // If the music is currently playing, stop it
    if (main_m->state() == QMediaPlayer::PlayingState)
        main_m->stop();

    // If the user has set the music and sounds to on, proceed with changing music.
    if (sounds_on)
    {
        // If the game music was stopped, restart it from the beginning. Otherwise, replay it again.
        if (game_m->state() == QMediaPlayer::StoppedState)
        {
            game_m->setPosition(0);
            game_m->play();
        }
        else
            game_m->play();
    }

    emit switchto(game_w);
}

void MainStackedWidget::changedtorules()
{
    emit switchto(rules_w);
}

void MainStackedWidget::changedtoresults(bool touched)
{
    survived_round = !touched;
    roundcomplete_T->stop();

    trojan_controller->pause();

    // Precaution to stop animation
    ucla_player->stop_running();

    // If the game music is currently playing, stop it from playing
    if (game_m->state() == QMediaPlayer::PlayingState)
        game_m->stop();

    // If the user has set the music and sounds to on, proceed with changing music.
    if (sounds_on)
    {
        // If the main music was stopped, restart it from the beginning. Otherwise, replay it again.
        if (main_m->state() == QMediaPlayer::StoppedState)
        {
            main_m->setPosition(0);
            music_transition_T->start();      // Waits 2.5 seconds before main_m plays
        }
        else
            music_transition_T->start();      // Waits 2.5 seconds before main_m plays
    }


    /* If the round was complete, play corresponding sound effect, change the round level,
       update the congratulations, and change the current widget to the roundcomplete window.
       Otherwise reset round level and change current widget to lostround window.
    */
    if (survived_round)
    {
        // If the user has set the music and sounds to on, play round won sound effect.
        if (sounds_on)
            roundcomplete_m->play();

        // If the game has been won, notify user. Otherwise, update the round info.
        if (round_number == 10)
        {
            roundcomplete_t->setText(QString::fromStdString("You've survived all rounds!"));
            roundcomplete_l->setAlignment(Qt::AlignCenter);
            roundcomplete_l->removeWidget(resultstogame_b);
            delete resultstogame_b;
        }
       else
        {
            roundcomplete_t->setText(QString::fromStdString("You've completed round " + std::to_string(round_number) + "!"));
            ++round_number;
        }
        emit switchto(roundcomplete_w);
    }
    else
    {
        // If the user has set the music and sounds to on, play round lost sound effect.
        if (sounds_on)
            lostround_m->play();

        round_number = 1;
        emit switchto(lostround_w);
    }
}

void MainStackedWidget::roundinfo()
{
    emit ucla_player->playertouched(false);
}

void MainStackedWidget::soundcontrol()
{
    /* If statement used to alternate betweeen sound on to sound off every time the sound button is clicked.
       If it's an odd time clicking, we turn all music and sounds off. Otherwise, set them on.
    */
    if (sounds_counter % 2)
    {
        // If the main music is playing, stop playing.
        if (main_m->state() == QMediaPlayer::PlayingState)
        {
            main_m->stop();
        }
        sounds_on = false;
    }
    else
    {
        main_m->play();
        sounds_on = true;
    }
    ucla_player->alter_sound(sounds_on);
    trojan_controller->alter_sound(sounds_on);
    ++sounds_counter;
}

MainStackedWidget::~MainStackedWidget()
{
    delete ucla_player;
    delete ucla_sprite;
    delete trojan_controller;
    delete game_scene;                    // game_view does NOT take ownership of game_scene
    delete main_m;
    delete game_m;
    delete roundcomplete_m;
    delete lostround_m;
    delete roundcomplete_T;
    delete music_transition_T;

}
