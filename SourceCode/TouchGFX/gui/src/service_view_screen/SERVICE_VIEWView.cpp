#include <gui/service_view_screen/SERVICE_VIEWView.hpp>

SERVICE_VIEWView::SERVICE_VIEWView()
{

}

void SERVICE_VIEWView::setupScreen()
{
    SERVICE_VIEWViewBase::setupScreen();
}

void SERVICE_VIEWView::tearDownScreen()
{
    SERVICE_VIEWViewBase::tearDownScreen();
}

void SERVICE_VIEWView::Light(uint16_t value)
{

    Unicode::snprintf(textArea1_1_1Buffer, TEXTAREA1_1_1_SIZE, "%u", value);
    textArea1_1_1.invalidate();
}

void SERVICE_VIEWView::Temp(uint16_t value)
{

    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", value);
    textArea1.invalidate();
}

void SERVICE_VIEWView::Hump(uint16_t value)
{

    Unicode::snprintf(textArea1_1Buffer, TEXTAREA1_1_SIZE, "%u", value);
    textArea1_1.invalidate();
}
