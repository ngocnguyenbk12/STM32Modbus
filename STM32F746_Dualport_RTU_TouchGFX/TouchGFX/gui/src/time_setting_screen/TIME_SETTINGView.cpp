#include <gui/time_setting_screen/TIME_SETTINGView.hpp>

extern "C"
{
    #include "stm32f7xx_hal.h"

    extern RTC_HandleTypeDef hrtc;
	extern RTC_TimeTypeDef RTC_Time;
	extern RTC_DateTypeDef RTC_Date;
}
TIME_SETTINGView::TIME_SETTINGView()
{

}

void TIME_SETTINGView::setupScreen()
{
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
    TIME_SETTINGViewBase::setupScreen();
}

void TIME_SETTINGView::tearDownScreen()
{
    TIME_SETTINGViewBase::tearDownScreen();
}

void TIME_SETTINGView::Time_UpButton()
{
    presenter->Test_Action();
}

void TIME_SETTINGView::Time_Up1()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Hours++;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
void TIME_SETTINGView::Time_Down1()
{
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Hours--;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
void TIME_SETTINGView::Time_Up2()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Minutes++;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
void TIME_SETTINGView::Time_Down2()
{
    HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Minutes--;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
void TIME_SETTINGView::Time_Up3()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Seconds++;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
void TIME_SETTINGView::Time_Down3()
{
	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
    RTC_Time.Seconds--;
    if(HAL_RTC_SetTime(&hrtc,&RTC_Time, RTC_FORMAT_BCD) != HAL_OK)
    {
        while(1);
    }
    analogClock1.setTime24Hour(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);
}
