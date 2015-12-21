/**
  @file
  @author Stefan Frings
*/

#include "actionbar.h"
#include <QIcon>
#include <QFontMetrics>
#include <QFont>
#include <QApplication>
#include <QStyleOption>
#include <QPainter>

ActionBar::ActionBar(QWidget *parent) : QWidget(parent) {
    setStyleSheet(
        "* {background:lightGray}"
        "QToolButton {height:1.6em}"
        "QToolButton QMenu::item {padding: 0.3em 1.5em 0.3em 1.5em; border: 1px solid transparent}"
        "QToolButton QMenu::item::selected {border-color: black}");

    //  "QToolButton#viewControl {font:bold}"

    // Create layout
    layout=new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    // App Icon and Up Button
    appIcon=new QToolButton();
    appIcon->setIcon(QIcon(":/icons/app"));
    appIcon->setAutoRaise(true);
    appIcon->setFocusPolicy(Qt::NoFocus);
    layout->addWidget(appIcon);

    // View Control Button
    viewControl=new QToolButton();
    viewControl->setObjectName("viewControl");
    viewControl->setText(QApplication::applicationDisplayName());
    viewControl->setAutoRaise(true);
    viewControl->setFocusPolicy(Qt::NoFocus);
    viewControl->setPopupMode(QToolButton::InstantPopup);
    viewMenu=new QMenu(viewControl);
    viewMenu->setStyle(&menuStyle); // needed because the icon size cannot be set by a StyleSheet
    viewControl->setMenu(viewMenu);
    layout->addWidget(viewControl);

    // Spacer
    layout->addStretch();

    // Action Overflow Button
    overflowButton=new QToolButton();
    overflowButton->setIcon(QIcon(":/icons/overflow"));
    overflowButton->setToolTip(tr("more"));
    overflowButton->setAutoRaise(true);
    overflowButton->setFocusPolicy(Qt::NoFocus);
    overflowButton->setPopupMode(QToolButton::InstantPopup);
    overflowMenu=new QMenu(overflowButton);
    overflowMenu->setStyle(&menuStyle); // needed because the icon size cannot be set by a StyleSheet
    overflowButton->setMenu(overflowMenu);
    layout->addWidget(overflowButton);
}

ActionBar::~ActionBar() {}

void ActionBar::resizeEvent(QResizeEvent* event) {
    int oldWidth=event->oldSize().width();
    int newWidth=event->size().width();
    qDebug("resize from %i to %i",oldWidth,newWidth);
    if (oldWidth!=newWidth) {
        adjustContent();
    }
}

void ActionBar::paintEvent(QPaintEvent*) {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }

void ActionBar::setTitle(const QString& title, bool showUpButton) {
    viewControl->setText(title);
    if (showUpButton) {
        (qApp->layoutDirection() == Qt::LeftToRight) ? appIcon->setIcon(QIcon(":/icons/app_up")) : appIcon->setIcon(QIcon(":/icons/app_up_rtl"));
        appIcon->setToolTip(tr("up"));
        connect(appIcon, &QToolButton::clicked, this, &ActionBar::appIconClicked);
    }
    else {
        appIcon->setIcon(QIcon(":/icons/app"));
        appIcon->setToolTip("");
        disconnect(appIcon, &QToolButton::clicked, this, &ActionBar::appIconClicked);
    }
    adjustContent();
}

QString ActionBar::getTitle() {
    return viewControl->text();
}

void ActionBar::appIconClicked() {
    emit up();
}

void ActionBar::adjustContent() {
    // Get size of one em (text height in pixels)
    int em=fontMetrics().height();

    viewMenu->repaint();

    // update size of app icon and overflow menu button
    appIcon->setIconSize(QSize(2*em,2*em));
    overflowButton->setIconSize(QSize(2*em,2*em));

    // Check if all action buttons fit into the available space with text beside icon.
    bool needOverflow=false;
    int space=width() - appIcon->sizeHint().width() - viewControl->sizeHint().width();
    for (int i=0; i<buttonActions.size(); i++) {
        QAction* action=buttonActions.at(i);
        QToolButton* button=actionButtons.at(i);
        if (action->isVisible()) {
            button->setIconSize(QSize(2*em,2*em));
            button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
            space-=button->sizeHint().width();
        }
    }
    if (space<0) {
        // Not enough space.
        // Check if all action buttons fit into the available space without text.
        int space=width() - appIcon->sizeHint().width() - viewControl->sizeHint().width();
        for (int i=0; i<buttonActions.size(); i++) {
            QAction* action=buttonActions.at(i);
            QToolButton* button=actionButtons.at(i);
            if (action->isVisible()) {
                button->setToolButtonStyle(Qt::ToolButtonIconOnly);
                space-=button->sizeHint().width();
            }
        }
        if (space<0) {
            // The buttons still don't fit, we need an overflow menu.
            needOverflow=true;
        }
    }

    // Calculate space available to display action buttons
    overflowMenu->clear();
    space=width() - appIcon->sizeHint().width() - viewControl->sizeHint().width();
    if (needOverflow) {
        space-=overflowButton->sizeHint().width();
    }

    // Show/Hide action buttons and overflow menu entries
    for (int i=0; i<buttonActions.size(); i++) {
        QAction* action=buttonActions.at(i);
        QToolButton* button=actionButtons.at(i);
        if (action->isVisible()) {
            space-=button->sizeHint().width();
            if (space>=0) {
                // show as button
                button->setDisabled(!buttonActions.at(i)->isEnabled());
                button->show();
            }
            else {
                // show as overflow menu entry
                button->hide();
                overflowMenu->addAction(action);
            }
        }
    }

    // Show/Hide the overflow menu button
    if (needOverflow) {
        overflowButton->show();
    }
    else {
        overflowButton->hide();
    }
}

void ActionBar::addNavigation(QAction* action) {
    QWidget::addAction(action);
    viewMenu->addAction(action);
    if (!viewMenu->isEmpty()) {
        viewControl->setMenu(viewMenu);
    }
}

void ActionBar::addNavigations(QList<QAction*> actions) {
    QWidget::addActions(actions);
    for (int i=0; i<actions.size(); i++) {
        addAction(actions.at(i));
    }
}

void ActionBar::removeNavigation(QAction* action) {
    QWidget::removeAction(action);
    viewMenu->removeAction(action);
    if (viewMenu->isEmpty()) {
        viewControl->setMenu(NULL);
    }
}

void ActionBar::addButton(QAction* action, int position) {
    if (position==-1) {
        position=buttonActions.size();
    }
    buttonActions.insert(position,action);
    QToolButton* button=new QToolButton();
    button->setText(action->text());
    button->setToolTip(action->text());
    button->setIcon(action->icon());
    button->setDisabled(!action->isEnabled());
    button->setFocusPolicy(Qt::NoFocus);
    button->setAutoRaise(true);
    connect(button,&QToolButton::clicked,action,&QAction::trigger);
    actionButtons.insert(position,button);
    layout->insertWidget(position+3,button);
}

void ActionBar::removeButton(QAction* action) {
    QToolButton* button=NULL;
    for (int i=0; i<buttonActions.size(); i++) {
        if (buttonActions.at(i)==action) {
            button=actionButtons.at(i);
            break;
        }
    }
    if (button) {
        layout->removeWidget(button);
        actionButtons.removeOne(button);
        delete button;
        buttonActions.removeOne(action);
    }
}

void ActionBar::openOverflowMenu() {
    if (overflowButton->isVisible()) {
        overflowButton->click();
    }
}


