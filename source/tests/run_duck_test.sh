#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-only
# DUCK measured: the depth, the way back, no click, 0.3's projects (tests/duck_test.c), under UBSan.
#   tests/run_duck_test.sh
set -e
cd "$(dirname "$0")/.."
mkdir -p build/duck
cc -O1 -g -Wall -Wno-unused-function -Wno-unused-parameter -DDINGHY_HOST -DAPP_VER="\"${APP_VER:-dev}\"" \
   -fsanitize=signed-integer-overflow,shift-exponent,bounds -fno-sanitize-recover=all \
   -Ifirmware/src -Ifirmware/gen -o build/duck/duck_test tests/duck_test.c -lm
build/duck/duck_test
