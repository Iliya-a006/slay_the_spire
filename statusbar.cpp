#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent)
{

}

StatusBar* StatusBar::m_instance = nullptr;
StatusBar* StatusBar::instance()
{
    if (!m_instance)
        m_instance = new StatusBar;
    return m_instance;
}

void StatusBar::status(QString text, int mSeconds)
{
    emit statusSignal(text, mSeconds);
}

StatusBar::~StatusBar()
{

}
