#ifndef LIGHT_VIEWPRESENTER_HPP
#define LIGHT_VIEWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class LIGHT_VIEWView;

class LIGHT_VIEWPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    LIGHT_VIEWPresenter(LIGHT_VIEWView& v);

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

    virtual ~LIGHT_VIEWPresenter() {};
    
    void LIGHT_Setnewvalue(uint16_t pin);
    void LIGHT_MB2Light(uint16_t pin);

    void LIGHT_Setnewvalue_0(bool State);
    void LIGHT_Setnewvalue_1(bool State); 
    void LIGHT_Setnewvalue_2(bool State);
    void LIGHT_Setnewvalue_3(bool State);
    void LIGHT_Setnewvalue_4(bool State);

private:
    LIGHT_VIEWPresenter();

    LIGHT_VIEWView& view;
};

#endif // LIGHT_VIEWPRESENTER_HPP
