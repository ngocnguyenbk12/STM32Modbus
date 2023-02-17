#ifndef SERVICE_VIEWVIEW_HPP
#define SERVICE_VIEWVIEW_HPP

#include <gui_generated/service_view_screen/SERVICE_VIEWViewBase.hpp>
#include <gui/service_view_screen/SERVICE_VIEWPresenter.hpp>

class SERVICE_VIEWView : public SERVICE_VIEWViewBase
{
public:
    SERVICE_VIEWView();
    virtual ~SERVICE_VIEWView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void Light(uint16_t value);
    virtual void Temp(uint16_t value);
    virtual void Hump(uint16_t value);
protected:
};

#endif // SERVICE_VIEWVIEW_HPP
