#ifndef AC_VIEWVIEW_HPP
#define AC_VIEWVIEW_HPP

#include <gui_generated/ac_view_screen/AC_VIEWViewBase.hpp>
#include <gui/ac_view_screen/AC_VIEWPresenter.hpp>

class AC_VIEWView : public AC_VIEWViewBase
{
public:
    AC_VIEWView();
    virtual ~AC_VIEWView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

/**         User Function           **/
    virtual void AC_TempUp();
    virtual void AC_TempDown();
    virtual void AC_setonoff();
    virtual void AC_TempLow();
    virtual void AC_TempHigh();
    virtual void AC_TempMed();
    virtual void AC_TempUpdate(uint16_t Value);
    virtual void AC_OnOffUpdate(bool State);
protected:
    uint16_t Counter = 20;  
};

#endif // AC_VIEWVIEW_HPP
