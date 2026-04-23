# miniRT

DK:
	RES="make SCREEN_WIDTH=1920 SCREEN_HEIGHT=1080"
2K:
	RES="make SCREEN_WIDTH=2560 SCREEN_HEIGHT=1440"
4K:
	RES="make SCREEN_WIDTH=3840 SCREEN_HEIGHT=2160"

eval $RES; make clean; for f in tests/*.rt tests/*/*.rt; do     echo "Running $f";     ./miniRT "$f" || echo "❌ crash or error: $f"; done; make fclean

make SCREEN_WIDTH=1920 SCREEN_HEIGHT=1080; make clean; for f in tests_bonus/*.rt tests_bonus/*/*.rt; do     echo "Running $f";     ./miniRT_bonus "$f" || echo "❌ crash or error: $f"; done; make fclean