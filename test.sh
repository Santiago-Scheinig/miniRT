#!/bin/bash

RESOLUTION=$1
FLAG=$2
VALGRIND=0

make fclean

if [ -z "$RESOLUTION" ]; then
  echo "Usage: $0 [DK, 2K, 4K, V (Valgrind)] <OPTIONAL: -f for fast mode>"
  exit 1
fi

if [ "$RESOLUTION" == "DK" ]; then
  RES="make SCREEN_WIDTH=1920 SCREEN_HEIGHT=1080"
elif [ "$RESOLUTION" == "2K" ]; then
  RES="make SCREEN_WIDTH=2560 SCREEN_HEIGHT=1440"
elif [ "$RESOLUTION" == "4K" ]; then
  RES="make SCREEN_WIDTH=3840 SCREEN_HEIGHT=2160"
elif [ "$RESOLUTION" == "V" ]; then
  RES="make SCREEN_WIDTH=300 SCREEN_HEIGHT=300"
  VALGRIND=1
else
  echo "Usage: $0 [DK, 2K, 4K, V (Valgrind)] <OPTIONAL: -f for fast mode>"
  exit 1
fi

if [ "$FLAG" = "-f" ]; then
	eval $RES
	make clean

	PIDS=()
	TESTS=()

	for f in tests/*.rt tests/*/*.rt; do
	echo "Running $f in background"
	if [ "$VALGRIND" -eq 1 ]; then
		valgrind --leak-check=full --error-exitcode=1 ./miniRT "$f" &
	else
		./miniRT "$f" &
	fi
	PIDS+=("$!")
	TESTS+=("$f")
	done

	for i in "${!PIDS[@]}"; do
		if ! wait "${PIDS[$i]}"; then
			echo "❌ crash or error: ${TESTS[$i]}"
		fi
	done
else 
	eval $RES
	make clean
	for f in tests/*.rt tests/*/*.rt; do
		echo "Running $f"
		if [ "$VALGRIND" -eq 1 ]; then
			valgrind --leak-check=full --error-exitcode=1 ./miniRT "$f" || echo "❌ crash or error: $f"
		else
			./miniRT "$f" || echo "❌ crash or error: $f"
		fi
	done
	make fclean
fi