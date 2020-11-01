//
// Created by alex2 on 31.10.2020.
//

#include "AProcess.h"
#include <Windows.h>

void AProcess::execute(const AString& command, const AString& args, const APath& workingDirectory) {
    ShellExecute(nullptr, L"runas", command.c_str(), args.c_str(),
                 workingDirectory.empty() ? nullptr : workingDirectory.c_str(), SW_SHOWNORMAL);
}