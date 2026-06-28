#pragma once

class Framework
{
public:
	static Framework& Get();

	bool Initialize();
	void Shutdown();

	void Run();

private:
	Framework() = default;

	bool CreateConsole();
	void DestroyConsole();

	void MainLoop();

	FILE* m_ConsoleOut = nullptr;
	std::unique_ptr<std::thread> m_MainThread;

	bool m_Initialized = false;
	bool m_Shutdown = false;
};
