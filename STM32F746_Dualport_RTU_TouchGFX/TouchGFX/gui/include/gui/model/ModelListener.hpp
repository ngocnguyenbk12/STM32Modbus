    #ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include "touchgfx/hal/Types.hpp"
class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }
    /*  AC Functions    */
    virtual void AC_Setnewvalue(unsigned short Value) {}
    virtual void AC_SetOnOff(bool State) {}

    /*  GPIO Function   */
    virtual void LIGHT_Setnewvalue_0(bool State) {}
    virtual void LIGHT_Setnewvalue_1(bool State) {}
    virtual void LIGHT_Setnewvalue_2(bool State) {}
    virtual void LIGHT_Setnewvalue_3(bool State) {}
    virtual void LIGHT_Setnewvalue_4(bool State) {}

    virtual void Light_Setnewvalue(uint16_t value) {}
    virtual void Temp_Setnewvalue(uint16_t value) {}
    virtual void Hump_Setnewvalue(uint16_t value) {}

    virtual void LIGHT_Setnewvalue(uint16_t pin) {}
    virtual void RTC_UpdateTime(uint8_t hour, uint8_t minute, uint8_t second) {}
    virtual void LIGHT_MB2Light(uint16_t pin) {}

    
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
