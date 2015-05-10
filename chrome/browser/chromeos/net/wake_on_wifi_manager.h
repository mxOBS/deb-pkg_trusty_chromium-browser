// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_NET_WAKE_ON_WIFI_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_NET_WAKE_ON_WIFI_MANAGER_H_

#include "base/containers/scoped_ptr_hash_map.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;

namespace base {
class DictionaryValue;
}

namespace chromeos {

// This class is responsible for managing the various wake-on-wifi related bits
// of functionality in chrome.  It is responsible for communicating the user's
// preferences to shill as well as listening for connections to the Google GCM
// servers and sending that connection information down to shill.  This class is
// owned by ChromeBrowserMainPartsChromeos.  This class is also NOT thread-safe
// and should only be called on the UI thread.
class WakeOnWifiManager : public content::NotificationObserver {
 public:
  enum WakeOnWifiFeature {
    WAKE_ON_NONE            = 0x00,
    WAKE_ON_PACKET          = 0x01,
    WAKE_ON_SSID            = 0x02,
    WAKE_ON_PACKET_AND_SSID = 0x03,
    NOT_SUPPORTED           = 0x04,
    INVALID                 = 0x08,
  };

  static WakeOnWifiManager* Get();

  WakeOnWifiManager();
  ~WakeOnWifiManager() override;

  // Should be called whenever the primary user changes their preference for the
  // wake-on-wifi features that should be enabled.
  void OnPreferenceChanged(WakeOnWifiFeature feature);

  // Returns true if wake-on-wifi features are supported. Returns false if we
  // have not yet determined whether wake-on-wifi features are supported.
  bool WakeOnWifiSupported();

  // Callback for getting the Wi-Fi device properties.
  void GetDevicePropertiesCallback(const std::string& device_path,
                                   const base::DictionaryValue& properties);

  // content::NotificationObserver override.
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override;

 private:
  void OnProfileAdded(Profile* profile);
  void OnProfileDestroyed(Profile* profile);

  WakeOnWifiFeature current_feature_;

  class WakeOnPacketConnectionObserver;
  base::ScopedPtrHashMap<Profile*, WakeOnPacketConnectionObserver>
      connection_observers_;

  content::NotificationRegistrar registrar_;

  base::WeakPtrFactory<WakeOnWifiManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WakeOnWifiManager);
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_NET_WAKE_ON_WIFI_MANAGER_H_