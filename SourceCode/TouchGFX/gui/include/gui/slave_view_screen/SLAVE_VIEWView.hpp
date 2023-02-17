#ifndef SLAVE_VIEWVIEW_HPP
#define SLAVE_VIEWVIEW_HPP

#include <gui_generated/slave_view_screen/SLAVE_VIEWViewBase.hpp>
#include <gui/slave_view_screen/SLAVE_VIEWPresenter.hpp>

class SLAVE_VIEWView : public SLAVE_VIEWViewBase
{
public:
    SLAVE_VIEWView();
    virtual ~SLAVE_VIEWView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void Slave_Button4();
    virtual void Slave_Button3();
    virtual void Slave_Button2();
    virtual void Slave_Button1();
    virtual void Slave_Button0();

protected:
};

#endif // SLAVE_VIEWVIEW_HPP
