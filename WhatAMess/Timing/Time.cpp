#include "Time.h"

Time::Time(): actualTime()
{

}

void Time::CalculateDeltaTime()
{
    actualTime.CalculateDeltaTime();
}

float Time::DeltaTime()
{
    return actualTime.DeltaTime();
}