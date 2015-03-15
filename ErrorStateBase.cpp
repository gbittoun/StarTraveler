#include "ErrorStateBase.h"

ErrorStateBase::ErrorStateBase() :
	errorState(SUCCESS)
{
}

ErrorStateBase::~ErrorStateBase()
{
}

bool ErrorStateBase::checkState()
{
	return errorState == SUCCESS;
}
