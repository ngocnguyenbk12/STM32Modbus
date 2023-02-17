#ifndef AC_VIEWPRESENTER_HPP
#define AC_VIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AC_VIEWView;

class AC_VIEWPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AC_VIEWPresenter(AC_VIEWView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~AC_VIEWPresenter() {};

    void AC_Setnewvalue(uint16_t Value);
    void AC_SetOnOff(bool State);

private:
    AC_VIEWPresenter();

    AC_VIEWView& view;
};

#endif // AC_VIEWPRESENTER_HPP
