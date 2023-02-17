#include <gui/time_setting_screen/TIME_SETTINGView.hpp>
#include <gui/time_setting_screen/TIME_SETTINGPresenter.hpp>

TIME_SETTINGPresenter::TIME_SETTINGPresenter(TIME_SETTINGView& v)
    : view(v)
{

}

void TIME_SETTINGPresenter::activate()
{

}

void TIME_SETTINGPresenter::deactivate()
{

}

void TIME_SETTINGPresenter::Test_Action()
{
    model->TestAction();
}