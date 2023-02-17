#ifndef SLAVE_VIEWPRESENTER_HPP
#define SLAVE_VIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SLAVE_VIEWView;

class SLAVE_VIEWPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SLAVE_VIEWPresenter(SLAVE_VIEWView& v);

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

    virtual ~SLAVE_VIEWPresenter() {};

private:
    SLAVE_VIEWPresenter();

    SLAVE_VIEWView& view;
};

#endif // SLAVE_VIEWPRESENTER_HPP
