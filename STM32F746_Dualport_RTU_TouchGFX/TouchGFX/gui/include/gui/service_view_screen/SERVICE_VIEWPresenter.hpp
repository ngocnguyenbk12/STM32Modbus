#ifndef SERVICE_VIEWPRESENTER_HPP
#define SERVICE_VIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SERVICE_VIEWView;

class SERVICE_VIEWPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SERVICE_VIEWPresenter(SERVICE_VIEWView& v);

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

    virtual ~SERVICE_VIEWPresenter() {};

    void Light_Setnewvalue(uint16_t value);
    void Temp_Setnewvalue(uint16_t value);
    void Hump_Setnewvalue(uint16_t value);

private:
    SERVICE_VIEWPresenter();

    SERVICE_VIEWView& view;
};

#endif // SERVICE_VIEWPRESENTER_HPP
