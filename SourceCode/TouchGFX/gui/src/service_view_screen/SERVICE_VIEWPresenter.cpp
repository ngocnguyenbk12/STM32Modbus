#include <gui/service_view_screen/SERVICE_VIEWView.hpp>
#include <gui/service_view_screen/SERVICE_VIEWPresenter.hpp>

SERVICE_VIEWPresenter::SERVICE_VIEWPresenter(SERVICE_VIEWView& v)
    : view(v)
{

}

void SERVICE_VIEWPresenter::activate()
{

}

void SERVICE_VIEWPresenter::deactivate()
{

}

void SERVICE_VIEWPresenter::Light_Setnewvalue(uint16_t value)
{
    view.Light(value);
}
void SERVICE_VIEWPresenter::Temp_Setnewvalue(uint16_t value)
{
    view.Temp(value);
}
void SERVICE_VIEWPresenter::Hump_Setnewvalue(uint16_t value)
{
    view.Hump(value);
}