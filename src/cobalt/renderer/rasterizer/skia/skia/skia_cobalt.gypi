# Copyright 2013 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.


# This gypi file contains all the Cobalt-specific enhancements to Skia.
# In component mode (shared_lib) it is folded into a single shared library with
# the Skia files but in all other cases it is a separate library.
{
  'dependencies': [
    '<(DEPTH)/base/base.gyp:base',
    '<(DEPTH)/cobalt/base/base.gyp:base',
    '<(DEPTH)/cobalt/configuration/configuration.gyp:configuration',
    '<(DEPTH)/starboard/starboard_headers_only.gyp:starboard_headers_only',
    '<(DEPTH)/third_party/freetype2/freetype2_cobalt.gyp:freetype2',
    '<(DEPTH)/third_party/libxml/libxml.gyp:libxml',
    'skia_library',
  ],

  'sources': [
    'config/SkUserConfig.h',
    'src/google_logging.cc',
    'src/gpu/gl/GrGLMakeNativeInterface_cobalt.cc',
    'src/ports/SkFontConfigParser_cobalt.cc',
    'src/ports/SkFontConfigParser_cobalt.h',
    'src/ports/SkFontMgr_cobalt.cc',
    'src/ports/SkFontMgr_cobalt.h',
    'src/ports/SkFontMgr_cobalt_factory.cc',
    'src/ports/SkFontStyleSet_cobalt.cc',
    'src/ports/SkFontStyleSet_cobalt.h',
    'src/ports/SkFontUtil_cobalt.cc',
    'src/ports/SkFontUtil_cobalt.h',
    'src/ports/SkFreeType_cobalt.cc',
    'src/ports/SkFreeType_cobalt.h',
    'src/ports/SkOSFile_cobalt.cc',
    'src/ports/SkOSFile_cobalt.h',
    'src/ports/SkStream_cobalt.cc',
    'src/ports/SkStream_cobalt.h',
    'src/ports/SkTypeface_cobalt.cc',
    'src/ports/SkTypeface_cobalt.h',
    'src/ports/SkTLS_cobalt.cc',
    'src/ports/SkTime_cobalt.cc',
  ],

  'include_dirs': [
    '<(SHARED_INTERMEDIATE_DIR)',
  ],

  'conditions': [
    ['OS=="starboard"', {
      'sources': [
        'src/ports/SkMemory_starboard.cc',
      ],
    }],
  ],
}
