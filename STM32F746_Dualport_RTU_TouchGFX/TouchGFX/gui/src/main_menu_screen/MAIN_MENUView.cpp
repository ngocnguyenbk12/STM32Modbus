#include <gui/main_menu_screen/MAIN_MENUView.hpp>

MAIN_MENUView::MAIN_MENUView()
{

}

void MAIN_MENUView::setupScreen()
{
    MAIN_MENUViewBase::setupScreen();
}

void MAIN_MENUView::tearDownScreen()
{
    MAIN_MENUViewBase::tearDownScreen();
}

void MAIN_MENUView::RTC_UpdateTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    analogClock1.setTime24Hour(hour, minute, second);
}