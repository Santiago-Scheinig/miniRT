# miniRT

make; for f in tests/*.rt tests/*/*.rt; do     echo "Running $f";     ./miniRT "$f" || echo "❌ crash or error: $f"; done; make fclean

make bonus; for f in tests_bonus/*.rt tests_bonus/*/*.rt; do     echo "Running $f";     ./miniRT_bonus "$f" || echo "❌ crash or error: $f"; done; make fclean