// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_VIZ_COMMON_RESOURCES_PLATFORM_COLOR_H_
#define COMPONENTS_VIZ_COMMON_RESOURCES_PLATFORM_COLOR_H_

#include "base/logging.h"
#include "base/macros.h"
#include "components/viz/common/resources/resource_format.h"
#include "gpu/command_buffer/common/capabilities.h"
#include "third_party/skia/include/core/SkTypes.h"

namespace viz {

class PlatformColor {
 public:
  enum SourceDataFormat { SOURCE_FORMAT_RGBA8, SOURCE_FORMAT_BGRA8 };

  static SourceDataFormat Format() {
    return SK_B32_SHIFT ? SOURCE_FORMAT_RGBA8 : SOURCE_FORMAT_BGRA8;
  }

  // Returns the most efficient supported format for textures that will be
  // software-generated and uploaded via TexImage2D et al.
  static ResourceFormat BestSupportedTextureFormat(
      const gpu::Capabilities& caps) {
    switch (Format()) {
      case SOURCE_FORMAT_BGRA8:
        return (caps.texture_format_bgra8888) ? BGRA_8888 : RGBA_8888;
      case SOURCE_FORMAT_RGBA8:
        return RGBA_8888;
    }
    NOTREACHED();
    return RGBA_8888;
  }

  // Returns the most efficient supported format for textures that will be
  // rastered in the gpu (bound as a framebuffer and drawn to).
  static ResourceFormat BestSupportedRenderBufferFormat(
      const gpu::Capabilities& caps) {
    switch (Format()) {
      case SOURCE_FORMAT_BGRA8:
        return (caps.render_buffer_format_bgra8888) ? BGRA_8888 : RGBA_8888;
      case SOURCE_FORMAT_RGBA8:
        return RGBA_8888;
    }
    NOTREACHED();
    return RGBA_8888;
  }

  // Return true if the given resource format has the same component order
  // as the platform color data format. Only supports formats that the
  // compositor can use for software raster.
  static bool SameComponentOrder(ResourceFormat format) {
    switch (format) {
      case RGBA_8888:
        return Format() == SOURCE_FORMAT_RGBA8;
      case BGRA_8888:
        return Format() == SOURCE_FORMAT_BGRA8;
      case RGBA_4444:
        return true;

      case ALPHA_8:
      case LUMINANCE_8:
      case RGB_565:
      case ETC1:
      case RED_8:
      case LUMINANCE_F16:
      case RGBA_F16:
      case R16_EXT:
      case BGR_565:
      case RG_88:
      case RGBX_8888:
      case BGRX_8888:
      case RGBX_1010102:
      case BGRX_1010102:
      case YVU_420:
      case YUV_420_BIPLANAR:
      case UYVY_422:
        break;
    }

    NOTREACHED();
    return false;
  }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(PlatformColor);
};

}  // namespace viz

#endif  // COMPONENTS_VIZ_COMMON_RESOURCES_PLATFORM_COLOR_H_
