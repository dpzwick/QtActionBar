#include "mainwindow.h"
#include <QVBoxLayout>
#include <QScroller>
#include <QApplication>
#include <QMessageBox>
#include <QTouchDevice>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    // Main layout of the application window
    QVBoxLayout* layout=new QVBoxLayout(this);
    layout->setMargin(0);

    // This is very important on mobile devices to adjust the size when the screen orientation changes
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    // Create the Action bar
    actionBar=createActionBar();
    layout->addWidget(actionBar);

    // Add a text field to the main window
    text=new QTextEdit();
    text->setFrameStyle(QFrame::NoFrame);
    text->viewport()->setAutoFillBackground(false);
    text->setReadOnly(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(text);

    // Disable scrollbars on devices with touch screen
    foreach(const QTouchDevice* device, QTouchDevice::devices()) {
        if (device->type()==QTouchDevice::TouchScreen) {
            text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            break;
        }
    }

    // Add touch gesture to the text field (scroll by swiping)
    QScroller::grabGesture(text, QScroller::TouchGesture);

    // Start with the main action
    goToMain();
}


ActionBar* MainWindow::createActionBar() {
    ActionBar* bar=new ActionBar(this);
    connect(bar,&ActionBar::up,this,&MainWindow::goToMain);

    // Add some navigation links to the action bar
    QAction* newsAction=new QAction(tr("News"),this);
    connect(newsAction,&QAction::triggered,this,&MainWindow::goToNews);
    bar->addNavigation(newsAction);

    QAction* weatherAction=new QAction(tr("Weather"),this);
    connect(weatherAction,&QAction::triggered,this,&MainWindow::goToWeather);
    bar->addNavigation(weatherAction);

    QAction* sportsAction= new QAction(tr("Sports"),this);
    connect(sportsAction,&QAction::triggered,this,&MainWindow::goToSports);
    bar->addNavigation(sportsAction);

    // Add some buttons to the action bar
    QAction* smallerAction=new QAction(QIcon(":/icons/smaller"),tr("Smaller"),this);
    connect(smallerAction, &QAction::triggered,this,&MainWindow::makeSmaller);
    bar->addButton(smallerAction);

    QAction* largerAction=new QAction(QIcon(":/icons/larger"),tr("Larger"),this);
    connect(largerAction,&QAction::triggered,this,&MainWindow::makeLarger);
    bar->addButton(largerAction);

    QAction* callAction=new QAction(QIcon(":/icons/call"),tr("Call"),this);
    connect(callAction,&QAction::triggered, this, &MainWindow::sayHello);
    bar->addButton(callAction);

    QAction* chatAction=new QAction(QIcon(":/icons/chat"),tr("Chat"),this);
    connect(chatAction,&QAction::triggered,this,&MainWindow::sayHello);
    bar->addButton(chatAction);

    QAction* emailAction=new QAction(QIcon(":/icons/email"),tr("Email"),this);
    connect(emailAction,&QAction::triggered,this,&MainWindow::sayHello);
    bar->addButton(emailAction);

    QAction* callAction1=new QAction(QIcon(":/icons/call"),tr("Something"),this);
    connect(callAction1,&QAction::triggered, this, &MainWindow::sayHello);
    bar->addButton(callAction1);

    QAction* callAction2=new QAction(QIcon(":/icons/call"),tr("Another action"),this);
    connect(callAction2,&QAction::triggered, this, &MainWindow::sayHello);
    bar->addButton(callAction2);

    QAction* callAction3=new QAction(QIcon(":/icons/call"),tr("Another action2"),this);
    connect(callAction3,&QAction::triggered, this, &MainWindow::sayHello);
    bar->addButton(callAction3);

    return bar;
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {
  int key = ev->key();

  // The menu key has no function by default.
  // But Android users expect that the menu button opens the overflow menu.
  // This works only in QT >= 5.4.0, see QTBUG-33276.
  if (key == Qt::Key_Menu) {
      qDebug("Catched menu button event");
      ev->accept();
      actionBar->openOverflowMenu();
      return;
  }

  // The Qt Framework closes the app when the back button is pressed.
  // But Android users expect that the back button navigates to the previous page.
  if (key == Qt::Key_Back && !isMainPage) {
      qDebug("Catched back button event");
      ev->accept();
      goToMain();
      return;
  }

  // Let QWidget process all other keys
  QWidget::keyPressEvent(ev);
}


void MainWindow::goToMain() {
    isMainPage=true;
    // Set the application title and disable up-navigation.
    actionBar->setTitle(QApplication::applicationDisplayName(),false);

    // Display a welcome message
    text->setText(tr("Hello World!"));
}

void MainWindow::goToNews() {
    isMainPage=false;
    // Since the user navigates to the news page, we display this now in the action bar.
    // Enable up-navigation, which leads back to the main page.
    actionBar->setTitle(tr("News"),true);

    // Display some other text.
    // The large text is good to test scrolling.
    text->setText(
                "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et "
                "dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet "
                "clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, "
                "consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed "
                "diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata "
                "sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy "
                "eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo "
                "duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
                "\n\n"
                "Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu "
                "feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril "
                "delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, "
                "sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat."
                "\n\n"
                "Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea "
                "commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel "
                "illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent "
                "luptatum zzril delenit augue duis dolore te feugait nulla facilisi."
                "\n\n"
                "Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer "
                "possim assum. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt "
                "ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation "
                "ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat."
                "\n\n"
                "Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu "
                "feugiat nulla facilisis."
                "\n\n"
                "At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est "
                "Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod "
                "tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo "
                "dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem "
                "ipsum dolor sit amet, consetetur sadipscing elitr, At accusam aliquyam diam diam dolore dolores duo eirmod eos "
                "erat, et nonumy sed tempor et et invidunt justo labore Stet clita ea et gubergren, kasd magna no rebum. sanctus "
                "sea sed takimata ut vero voluptua. est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur."
                );
}

void MainWindow::goToWeather() {
    isMainPage=false;
    actionBar->setTitle(tr("Weather"),true);
    text->setText(tr("It will rain the whole next week"));
}

void MainWindow::goToSports() {
    isMainPage=false;
    actionBar->setTitle(tr("Sports"),true);
    text->setText(tr("Switch your computer off and go out to make sports"));
}

float MainWindow::getPointSize(const QFont& font) {
    // Workaround against QTBUG-4958
    // QFontInfo can properly convert from pixels to points but returns
    // wrong value if the font has already a size in points.
    if (font.pixelSize() != -1) {
        // Size is set in pixels, convert to points
        float pointSize=QFontInfo(font).pointSizeF();
        qDebug("Converting pixelSize %i to pointSize %f",font.pixelSize(),pointSize);
        return pointSize;
    }
    else {
        // Size is set in points, no conversion needed
        return font.pointSizeF();
    }
}

void MainWindow::makeSmaller() {
    // Make the text field font smaller
    float oldSize=getPointSize(text->font());
    if (oldSize>4) {
        float newSize=oldSize-2;
        qDebug("Change font size from %f to %f",oldSize,newSize);
        text->setFont(QFont("sans",newSize));
    }
}

void MainWindow::makeLarger() {
     // Make the text field font larger
    float oldSize=getPointSize(text->font());
    if (oldSize<100) {
        float newSize=oldSize+2;
        qDebug("Change font size from %f to %f",oldSize,newSize);
        text->setFont(QFont("sans",newSize));
    }
}

void MainWindow::sayHello() {
    QMessageBox::information(NULL,tr("Message"),tr("Hello"));
}


