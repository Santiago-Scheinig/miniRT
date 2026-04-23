#!/bin/bash

RESOLUTION=$1
FAST=$2

if [ -z "$RESOLUTION" ]; then
  echo "Usage: $0 [DK, 2K, 4K] <OPTIONAL: -f for fast mode>"
  exit 1
fi

if [ "$RESOLUTION" == "DK" ]; then
  RES="make SCREEN_WIDTH=1920 SCREEN_HEIGHT=1080"
elif [ "$RESOLUTION" == "2K" ]; then
  RES="make SCREEN_WIDTH=2560 SCREEN_HEIGHT=1440"
elif [ "$RESOLUTION" == "4K" ]; then
  RES="make SCREEN_WIDTH=3840 SCREEN_HEIGHT=2160"
else
  echo "Usage: $0 [DK, 2K, 4K] <OPTIONAL: -f for fast mode>"
  exit 1
fi

if [ "$FAST" = "-f" ]; then
	eval $RES
	make clean

	PIDS=()
	TESTS=()

	for f in tests/*.rt tests/*/*.rt; do
	echo "Running $f in background"
	./miniRT "$f" &
	PIDS+=("$!")
	TESTS+=("$f")
	done

	for i in "${!PIDS[@]}"; do
	if ! wait "${PIDS[$i]}"; then
		echo "❌ crash or error: ${TESTS[$i]}"
	fi
	done
else 
	eval $RES; make clean; for f in tests/*.rt tests/*/*.rt; do     echo "Running $f";     ./miniRT "$f" || echo "❌ crash or error: $f"; done; make fclean
fi