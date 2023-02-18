#ifndef TIME_SETTINGVIEW_HPP
#define TIME_SETTINGVIEW_HPP

#include <gui_generated/time_setting_screen/TIME_SETTINGViewBase.hpp>
#include <gui/time_setting_screen/TIME_SETTINGPresenter.hpp>

class TIME_SETTINGView : public TIME_SETTINGViewBase
{
public:
    TIME_SETTINGView();
    virtual ~TIME_SETTINGView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    
    virtual void Time_UpButton();
    virtual void Time_Up1();
    virtual void Time_Up2();
    virtual void Time_Up3();
    virtual void Time_Down1();
    virtual void Time_Down2();
    virtual void Time_Down3();
protected:
};

#endif // TIME_SETTINGVIEW_HPP
