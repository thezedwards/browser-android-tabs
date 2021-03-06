// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_COMPONENTS_WEB_APP_ICON_GENERATOR_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_COMPONENTS_WEB_APP_ICON_GENERATOR_H_

#include <map>
#include <set>
#include <vector>

#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkColor.h"
#include "url/gurl.h"

namespace web_app {

namespace icon_size {

// An iteration of valid icon sizes in pixels. Allows client code to declare a
// subset of supported sizes that are guaranteed to be valid.
enum {
  k512 = 512,
  k256 = 256,
  k128 = 128,
  k96 = 96,
  k64 = 64,
  k48 = 48,
  k32 = 32,
  k24 = 24,
  k16 = 16,
  kInvalid = 0,
};

}  // namespace icon_size

struct BitmapAndSource {
  BitmapAndSource();
  BitmapAndSource(const GURL& source_url_p, const SkBitmap& bitmap_p);
  ~BitmapAndSource();

  GURL source_url;
  SkBitmap bitmap;
};

// This finds the closest not-smaller bitmap in |bitmaps| for each size in
// |sizes| and resizes it to that size. This returns a map of sizes to bitmaps
// which contains only bitmaps of a size in |sizes| and at most one bitmap of
// each size.
std::map<int, BitmapAndSource> ConstrainBitmapsToSizes(
    const std::vector<BitmapAndSource>& bitmaps,
    const std::set<int>& sizes);

// Generates a square container icon of |output_size| by drawing the given
// |letter| into a rounded background of |color|.
SkBitmap GenerateBitmap(int output_size, SkColor color, char letter);

// Resize icons to the accepted sizes, and generate any that are missing.
// Note that |app_url| is the launch URL for the app.
// Output: |generated_icon_color| is the color to use if an icon needs to be
// generated for the web app.
std::map<int, BitmapAndSource> ResizeIconsAndGenerateMissing(
    const std::vector<BitmapAndSource>& icons,
    const std::set<int>& sizes_to_generate,
    const GURL& app_url,
    SkColor* generated_icon_color);

}  // namespace web_app

#endif  // CHROME_BROWSER_WEB_APPLICATIONS_COMPONENTS_WEB_APP_ICON_GENERATOR_H_
