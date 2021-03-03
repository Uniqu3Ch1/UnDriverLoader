

#include "pch.h"

DriverHelp::DriverHelp()
{

}

bool DriverHelp::RegisterDriver()
{
	SC_HANDLE scm;
	SC_HANDLE service;
	DWORD err;
	scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (scm != NULL && pszDriverName != NULL && pszDriverPath != NULL)
	{
		service = CreateServiceW(scm, pszDriverName, pszDriverName, NULL, SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, pszDriverPath, NULL, NULL, NULL, NULL, NULL);
		if (service != NULL)
		{
			CloseServiceHandle(service);
			return true;
		}
		if (service == NULL)
		{
			err = GetLastError();
			if (err == 0x431)
			{
				return true;
			}
		}
	}
	return false;
}

bool DriverHelp::RunDriver()
{
	bool result = false;
	SC_HANDLE service;
	SC_HANDLE scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
	if (scm != NULL && pszDriverName != NULL)
	{
		service = OpenServiceW(scm, pszDriverName, SERVICE_START);
		if (service)
		{
			result = StartServiceW(service, NULL, NULL);
			CloseServiceHandle(service);
		}
		CloseServiceHandle(scm);
	}
	
	return result;
}

bool DriverHelp::StopDriver()
{
	SC_HANDLE scm;
	SC_HANDLE service;
	SERVICE_STATUS status;
	bool result = false;
	scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
	if (scm != NULL && pszDriverName != NULL)
	{
		service = OpenServiceW(scm, pszDriverName, SERVICE_STOP);
		if (service)
		{
			result = ControlService(service, SERVICE_CONTROL_STOP, &status);
			CloseServiceHandle(service);
		}
		CloseServiceHandle(scm);
	}

	return result;
}

bool DriverHelp::UnRegisterDriver()
{
	bool result = false;
	SC_HANDLE scm;
	SC_HANDLE service;
	scm = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
	if (scm != NULL && pszDriverName != NULL)
	{
		service = OpenServiceW(scm, pszDriverName, DELETE);
		if (service)
		{
			result = DeleteService(service);
			CloseServiceHandle(service);
		}
		CloseServiceHandle(scm);
	}
	return result;
}

void DriverHelp::setName(CString DriverName)
{
	pszDriverName = DriverName.AllocSysString();
}

void DriverHelp::setPath(CString DriverPath)
{
	pszDriverPath = DriverPath.AllocSysString();
}
