#ifdef Q_OS_WIN
#include <windows.h>
#endif

#ifdef Q_OS_UNIX
#include <signal.h>
#include <unistd.h>
#endif

inline void forceExit()
{
#ifdef Q_OS_WIN
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, GetCurrentProcessId());
    if (hProcess != NULL) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }
#elif defined(Q_OS_UNIX)
    kill(getpid(), SIGKILL);
#endif
}
