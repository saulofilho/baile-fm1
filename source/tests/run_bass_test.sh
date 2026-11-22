#!/bin/sh
# SPDX-License-Identifier: GPL-3.0-only
# GRAVE+ measured: the harmonics for small speakers, the headroom, no click (tests/bass_test.c), under UBSan.
#   tests/run_bass_test.sh
set -e
cd "$(dirname "$0")/.."
mkdir -p build/bass
cc -O1 -g -Wall -Wno-unused-function -Wno-unused-parameter -DDINGHY_HOST -DAPP_VER="\"${APP_VER:-dev}\"" \
   -fsanitize=signed-integer-overflow,shift-exponent,bounds -fno-sanitize-recover=all \
   -Ifirmware/src -Ifirmware/gen -o build/bass/bass_test tests/bass_test.c -lm
build/bass/bass_test
