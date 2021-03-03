#pragma once



class DriverHelp
{
private:


	LPCWSTR pszDriverName = NULL;
	LPCWSTR pszDriverPath = NULL;

public:
	DriverHelp();

	bool RegisterDriver();
	bool RunDriver();
	bool StopDriver();
	bool UnRegisterDriver();
	void setPath(CString DriverPath);
	void setName(CString DriverName);


};

