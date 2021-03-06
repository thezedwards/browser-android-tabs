// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.chrome.browser.test;

import org.junit.rules.ExternalResource;

import org.chromium.content_public.browser.test.NativeLibraryTestRule;

/** JUnit test rule which enables tests to force certificate verification results. */
public class MockCertVerifierRuleAndroid extends ExternalResource {
    private NativeLibraryTestRule mNativeLibraryTestRule;

    private long mNativePtr;

    // Certificate verification result to force.
    private int mResult;

    public MockCertVerifierRuleAndroid(NativeLibraryTestRule nativeLibraryTestRule, int result) {
        mNativeLibraryTestRule = nativeLibraryTestRule;
        mResult = result;
    }

    @Override
    protected void before() {
        mNativeLibraryTestRule.loadNativeLibraryNoBrowserProcess();
        mNativePtr = nativeInit(mResult);
        nativeSetUp(mNativePtr);
    }

    @Override
    protected void after() {
        nativeTearDown(mNativePtr);
        mNativePtr = 0;
    }

    private static native long nativeInit(int result);
    private native void nativeSetUp(long nativeMockCertVerifierRuleAndroid);
    private native void nativeTearDown(long nativeMockCertVerifierRuleAndroid);
}
