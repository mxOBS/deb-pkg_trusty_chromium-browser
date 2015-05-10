// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#ifndef TestInterfaceEventInit_h
#define TestInterfaceEventInit_h

#include "core/events/EventInitDictionary.h"
#include "platform/heap/Handle.h"
#include "wtf/text/WTFString.h"

namespace blink {

class TestInterfaceEventInit : public EventInitDictionary {
    ALLOW_ONLY_INLINE_ALLOCATION();
public:
    TestInterfaceEventInit();

    bool hasStringMember() const { return !m_stringMember.isNull(); }
    String stringMember() const { return m_stringMember; }
    void setStringMember(String value) { m_stringMember = value; }

    virtual void trace(Visitor*);

private:
    String m_stringMember;

    friend class V8TestInterfaceEventInit;
};

} // namespace blink

#endif // TestInterfaceEventInit_h