/*
 * Copyright (c) 2017 Intel Corporation. All rights reserved.
 */

#ifndef WOOGEEN_BASE_NETWORKMONITORIOS_H_
#define WOOGEEN_BASE_NETWORKMONITORIOS_H_

#include <SystemConfiguration/SystemConfiguration.h>

#include <memory>
#include <mutex>

#include "webrtc/base/network.h"
#include "webrtc/base/thread.h"

namespace woogeen {
namespace base {

/**
 * Borrowed from Chromium's src/net/base/network_change_notifier_mac.h(cc)
 *
 * Modified some code to eliminate dependencies on Chrome code and remove macOS
 * support.
 */
class NetworkMonitorIos : public rtc::NetworkMonitorBase {
 public:
  NetworkMonitorIos();
  ~NetworkMonitorIos() override;

  void Init();
  void Start() override;
  void Stop() override;

  // Always return unknown because it is not used anywhere.
  rtc::AdapterType GetAdapterType(const std::string& interface_name) override;

 private:
  void StartReachabilityNotifications();
  void StopReachabilityNotifications();

  static void ReachabilityCallback(SCNetworkReachabilityRef target,
                                   SCNetworkConnectionFlags flags,
                                   void* notifier);

  SCNetworkReachabilityRef reachability_;

  RTC_DISALLOW_COPY_AND_ASSIGN(NetworkMonitorIos);
};

class NetworkMonitorFactoryIos : public rtc::NetworkMonitorFactory {
 public:
  NetworkMonitorFactoryIos(){};

  rtc::NetworkMonitorInterface* CreateNetworkMonitor() override;

 private:
  RTC_DISALLOW_COPY_AND_ASSIGN(NetworkMonitorFactoryIos);
};
}
}

#endif  // WOOGEEN_BASE_NETWORKMONITORIOS_H_
