//
//  AppLaunchTime.c
//
//  Created by Adam Fallon on 24/09/2020.
//
//  This code is used to ask the kernel how long our app spent in "pre-main" time.
//  https://man.openbsd.org/sysctl

#include "AppLaunchTime.h"
#include <sys/sysctl.h>
#include <sys/unistd.h>

int64_t TTLAppLaunchTime() {
    struct kinfo_proc processInfo;
    size_t processInfoSize = sizeof(struct kinfo_proc);
    
    /// Management Information Base
    int mib[4U] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid() };
    
    /// Get process info for current process
    int sysctl_response = sysctl(mib, sizeof(mib)/sizeof(int), &processInfo, &processInfoSize, NULL, 0);
    
    if (sysctl_response != 0) {
        /// Non-zero exit code - we were denied information from sysctl
        return -1;
    } else {
        /// Convert timeval to time in milliseconds
        return (processInfo.kp_proc.p_starttime.tv_sec * 1000) + (processInfo.kp_proc.p_starttime.tv_usec / 1000);
    }
}
