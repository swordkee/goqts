// +build cgo

// Copyright 2012 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package goqts

// #cgo linux LDFLAGS: -fPIC -L${SRCDIR}/api/QTSApi_v2.6.0/include -O2 -W -Wall -Wno-unused-parameter,-rpath=${SRCDIR}/api/QTSApi_v2.6.0/include -lGTAQTSApi -std=c++11
// #cgo linux CPPFLAGS: -fPIC -I${SRCDIR}/api/QTSApi_v2.6.0/include
import "C"
