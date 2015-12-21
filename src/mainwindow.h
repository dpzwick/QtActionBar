#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "actionbar.h"
#include <QWidget>
#include <QTextEdit>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    /** Handle the back key and menu key of mobile devices. */
    void keyPressEvent(QKeyEvent *ev);

private:
    /** Create the action bar */
    ActionBar* createActionBar();

    /** Get the size of a font in points, eventually convert from pixels */
    float getPointSize(const QFont& font);

    /** Pointer to the action bar. */
    ActionBar* actionBar;

    /** Pointer to the text field. */
    QTextEdit* text;

    /** Indicates whether the user is on the main page. */
    bool isMainPage;

public slots:
    /** Action handler for the up navigation, goes back to the main page */
    void goToMain();

    /** Action handler for the navigation to the topic: News */
    void goToNews();

    /** Action handler for the navigation to the topic: Weather */
    void goToWeather();

    /** Action handler for the navigation to the topic: Sports */
    void goToSports();

    /** Action handler to make everything smaller, including the action bar */
    void makeSmaller();

    /** Action handler to make everything larger, including the action bar */
    void makeLarger();

    /** Action handler for the action buttons */
    void sayHello();
};

#endif // MAINWINDOW_H
