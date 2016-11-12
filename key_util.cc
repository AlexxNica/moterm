// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "apps/moterm/key_util.h"

#include <hid/usages.h>

#include "apps/mozart/services/input/input_events.fidl.h"
#include "lib/ftl/logging.h"

// TODO(vtl): Handle more stuff and verify that we're consistent about the
// sequences we generate.
// TODO(vtl): In particular, our implementation of keypad_application_mode is
// incomplete.
std::string GetInputSequenceForKeyPressedEvent(const mozart::Event& key_event,
                                               bool keypad_application_mode) {
  FTL_DCHECK(key_event.action == mozart::EventType::KEY_PRESSED);
  FTL_CHECK(key_event.key_data);
  const mozart::KeyData& key_data = *key_event.key_data;

  // FTL_LOG(INFO) << "Key pressed:"
  //               << "\n  hid_usage = " << key_data.hid_usage
  //               << "\n  code_point = " << key_data.code_point;

  uint32_t non_ascii =
      key_data.modifiers & (mozart::CONTROL | mozart::ALT | mozart::GUI);

  if (!non_ascii && key_data.code_point) {
    if (key_data.code_point > 128) {
      FTL_NOTIMPLEMENTED();
      return std::string();
    }
    return std::string(1, static_cast<char>(key_data.code_point));
  }

  switch (key_data.hid_usage) {
    case HID_USAGE_KEY_BACKSPACE:
      // Have backspace send DEL instead of BS.
      return std::string("\x7f");
    case HID_USAGE_KEY_ESC:
      return std::string("\33");
    case HID_USAGE_KEY_PAGEDOWN:
      return std::string("\33[6~");
    case HID_USAGE_KEY_PAGEUP:
      return std::string("\33[5~");
    case HID_USAGE_KEY_END:
      return std::string("\33[F");
    case HID_USAGE_KEY_HOME:
      return std::string("\33[H");
    case HID_USAGE_KEY_LEFT:
      return std::string("\33[D");
    case HID_USAGE_KEY_UP:
      return std::string("\33[A");
    case HID_USAGE_KEY_RIGHT:
      return std::string("\33[C");
    case HID_USAGE_KEY_DOWN:
      return std::string("\33[B");
    case HID_USAGE_KEY_INSERT:
      return std::string("\33[2~");
    case HID_USAGE_KEY_DELETE:
      return std::string("\33[3~");
    case HID_USAGE_KEY_ENTER:
      return std::string("\n");
    case HID_USAGE_KEY_TAB:
      return std::string("\t");
    case HID_USAGE_KEY_A:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 1);
      }
    case HID_USAGE_KEY_B:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 2);
      }
    case HID_USAGE_KEY_C:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 3);
      }
    case HID_USAGE_KEY_D:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 4);
      }
    case HID_USAGE_KEY_E:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 5);
      }
    case HID_USAGE_KEY_F:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 6);
      }
    case HID_USAGE_KEY_H:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 8);
      }
    case HID_USAGE_KEY_K:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 11);
      }
    case HID_USAGE_KEY_L:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 12);
      }
    case HID_USAGE_KEY_N:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 14);
      }
    case HID_USAGE_KEY_P:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 16);
      }
    case HID_USAGE_KEY_T:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 20);
      }
    case HID_USAGE_KEY_U:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 21);
      }
    case HID_USAGE_KEY_W:
      if (key_data.modifiers & mozart::CONTROL) {
        return std::string(1, 23);
      }
    default:
      FTL_NOTIMPLEMENTED() << " hid_usage = " << key_data.hid_usage;
  }

  return std::string();
}
