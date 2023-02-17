#include <gui/ac_view_screen/AC_VIEWView.hpp>
#include <gui/ac_view_screen/AC_VIEWPresenter.hpp>

AC_VIEWPresenter::AC_VIEWPresenter(AC_VIEWView& v)
    : view(v)
{

}

void AC_VIEWPresenter::activate()
{

}

void AC_VIEWPresenter::deactivate()
{

}

void AC_VIEWPresenter::AC_Setnewvalue(uint16_t Value)
{
    view.AC_TempUpdate(Value);
}   
void AC_VIEWPresenter::AC_SetOnOff(bool State)
{
    view.AC_OnOffUpdate(State);
}   