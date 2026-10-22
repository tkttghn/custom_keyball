#!/bin/sh
set -eu

keymap_dir=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
test_dir=$(mktemp -d "${TMPDIR:-/tmp}/keyball-pointer-accel.XXXXXX")
trap 'rm -f "$test_dir/enabled" "$test_dir/disabled" "$test_dir/scroll"; rmdir "$test_dir"' EXIT

for enabled in 1 0; do
    if [ "$enabled" = 1 ]; then output=enabled; else output=disabled; fi
    clang -std=c11 -Wall -Wextra -Werror -fsanitize=address,undefined \
        -DCONDUCTOR_POINTER_ACCEL_ENABLE="$enabled" -I "$keymap_dir" \
        "$keymap_dir/pointer_accel.c" "$keymap_dir/tests/test_pointer_accel.c" \
        -o "$test_dir/$output"
    "$test_dir/$output"
done

clang -std=c11 -Wall -Wextra -Werror -fsanitize=address,undefined -I "$keymap_dir" \
    "$keymap_dir/scroll_axis.c" "$keymap_dir/tests/test_scroll_axis.c" -o "$test_dir/scroll"
"$test_dir/scroll"
