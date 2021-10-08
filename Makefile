# SPDX-License-Identifier: LGPL-2.1-or-later

all:
	meson build
	ninja -C build

install:
	DESTDIR="../install" ninja -C build install

clean:
	rm -rf build install
