// Copyright 2017 The Lynx Authors. All rights reserved.

#ifndef LYNX_ANDROID_USER_AGENT_H
#define LYNX_ANDROID_USER_AGENT_H

#include <string>
#include <base/threading/read_write_lock.h>

#include "runtime/config.h"
#include "config/global_config_data.h"

#define DEFAULT_USER_AGENT ((((std::string(APP_NAME) + "/") + VERSION) + " ") + PLATFORM)

namespace jscore {
    class UserAgent {
    public:
        UserAgent() {
            user_agent_ = DEFAULT_USER_AGENT + " ("
                        + config::GlobalConfigData::GetInstance()->device_info() + ")";
        }

        void Set(const std::string& ua) {
            lock_.WriteLock();
            user_agent_ = ua;
            lock_.WriteUnlock();
        }

        inline const std::string Get() {
            std::string temp;
            lock_.ReadLock();
            temp = user_agent_;
            lock_.ReadUnlock();
            return temp;
        }

    private:
        std::string user_agent_;
        base::ReadWriteLock lock_;
    };
}

#endif //LYNX_ANDROID_USER_AGENT_H
