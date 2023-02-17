#include <gui/light_view_screen/LIGHT_VIEWView.hpp>
#include <gui/light_view_screen/LIGHT_VIEWPresenter.hpp>

LIGHT_VIEWPresenter::LIGHT_VIEWPresenter(LIGHT_VIEWView& v)
    : view(v)
{

}

void LIGHT_VIEWPresenter::activate()
{

}

void LIGHT_VIEWPresenter::deactivate()
{

}

void LIGHT_VIEWPresenter::LIGHT_Setnewvalue(uint16_t pin)
{
    view.LIGHT_Updater(pin);
}

void LIGHT_VIEWPresenter::LIGHT_MB2Light(uint16_t pin)
{
    view.Light_Updater(pin);
}

void LIGHT_VIEWPresenter::LIGHT_Setnewvalue_0(bool State)
{
    view.LIGHT_Update_0(State);
}
void LIGHT_VIEWPresenter::LIGHT_Setnewvalue_1(bool State)
{
    view.LIGHT_Update_1(State);
}
void LIGHT_VIEWPresenter::LIGHT_Setnewvalue_2(bool State)
{
    view.LIGHT_Update_2(State);
}
void LIGHT_VIEWPresenter::LIGHT_Setnewvalue_3(bool State)
{
    view.LIGHT_Update_3(State);
}
void LIGHT_VIEWPresenter::LIGHT_Setnewvalue_4(bool State)
{
    view.LIGHT_Update_4(State);
}
