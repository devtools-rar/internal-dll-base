#include "pch.h"
#include "framework.h"

Framework& Framework::Get()
{
	static Framework instance;
	return instance;
}

bool Framework::Initialize()
{
	if (m_Initialized)
		return true;

	CreateConsole();

	m_Initialized = true;
	return true;
}

void Framework::Shutdown()
{
	if (!m_Initialized)
		return;

	m_Shutdown = true;

	if (m_MainThread && m_MainThread->joinable())
		m_MainThread->join();

	DestroyConsole();
	m_Initialized = false;
}

void Framework::Run()
{
	if (!m_Initialized)
		return;

	m_MainThread = std::make_unique<std::thread>(&Framework::MainLoop, this);
}

void Framework::MainLoop()
{
	while (!m_Shutdown)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

bool Framework::CreateConsole()
{
	if (!AllocConsole())
		return false;

	freopen_s(&m_ConsoleOut, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Internal Base");

	printf("[+] Base initialized\n");

	return true;
}

void Framework::DestroyConsole()
{
	if (m_ConsoleOut)
		fclose(m_ConsoleOut);

	FreeConsole();
}
