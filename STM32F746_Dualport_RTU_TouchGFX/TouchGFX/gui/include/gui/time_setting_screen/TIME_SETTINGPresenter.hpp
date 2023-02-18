#ifndef TIME_SETTINGPRESENTER_HPP
#define TIME_SETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class TIME_SETTINGView;

class TIME_SETTINGPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    TIME_SETTINGPresenter(TIME_SETTINGView& v);

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

    virtual ~TIME_SETTINGPresenter() {};

    virtual void Test_Action();
private:
    TIME_SETTINGPresenter();

    TIME_SETTINGView& view;
};

#endif // TIME_SETTINGPRESENTER_HPP
