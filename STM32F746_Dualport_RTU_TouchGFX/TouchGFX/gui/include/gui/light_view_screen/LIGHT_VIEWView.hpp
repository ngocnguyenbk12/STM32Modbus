#ifndef LIGHT_VIEWVIEW_HPP
#define LIGHT_VIEWVIEW_HPP

#include <gui_generated/light_view_screen/LIGHT_VIEWViewBase.hpp>
#include <gui/light_view_screen/LIGHT_VIEWPresenter.hpp>

class LIGHT_VIEWView : public LIGHT_VIEWViewBase
{
public:
    LIGHT_VIEWView();
    virtual ~LIGHT_VIEWView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void Light_Button0();
    virtual void Light_Button1();
    virtual void Light_Button2();
    virtual void Light_Button3();
    virtual void Light_Button4();
    virtual void LIGHT_Updater(uint16_t pin);
    virtual void Light_Updater(uint16_t pin);

    virtual void LIGHT_Update_0(bool State);
    virtual void LIGHT_Update_1(bool State);
    virtual void LIGHT_Update_2(bool State);
    virtual void LIGHT_Update_3(bool State);
    virtual void LIGHT_Update_4(bool State);
protected:
};

#endif // LIGHT_VIEWVIEW_HPP
