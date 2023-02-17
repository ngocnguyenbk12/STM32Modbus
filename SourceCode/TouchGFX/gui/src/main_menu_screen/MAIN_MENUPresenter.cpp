#include <gui/main_menu_screen/MAIN_MENUView.hpp>
#include <gui/main_menu_screen/MAIN_MENUPresenter.hpp>

MAIN_MENUPresenter::MAIN_MENUPresenter(MAIN_MENUView& v)
    : view(v)
{

}

void MAIN_MENUPresenter::activate()
{

}

void MAIN_MENUPresenter::deactivate()
{

}

void MAIN_MENUPresenter::RTC_UpdateTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    view.RTC_UpdateTime(hour,minute,second);
}
