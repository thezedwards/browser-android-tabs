// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_FEATURES_H_
#define IOS_CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_FEATURES_H_

#include "base/feature_list.h"

// Feature flag to enable new Clear Browsing Data UI.
extern const base::Feature kNewClearBrowsingDataUI;

// Feature to use the clear browsing data from web instead of the one from
// chrome.
extern const base::Feature kWebClearBrowsingData;

// Whether the new Clear Browsing Data UI is enabled.
bool IsNewClearBrowsingDataUIEnabled();

#endif  // IOS_CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_FEATURES_H_
