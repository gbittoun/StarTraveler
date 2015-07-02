#include "ErrorStateBase.h"

ErrorStateBase::ErrorStateBase() :
	errorState(SUCCESS)
{
}

ErrorStateBase::~ErrorStateBase()
{
}

bool ErrorStateBase::checkState() const
{
	return errorState == SUCCESS;
}
