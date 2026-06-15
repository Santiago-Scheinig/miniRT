#!/bin/bash

RESOLUTION=$1
VALGRIND=0
NORM=0
OP_FILE=vlog.txt
NORM_FILE=norm.txt

# Colors
BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
RESET='\033[0m'

NORM_DIRS=(
  ./src
  ./src/rtapp
  ./src/rtapp/debug
  ./src/rtapp/init
  ./src/rtapp/init/parser
  ./src/rtapp/render
  ./libs/librt/src/rtelm
  ./libs/librt/src/rtelm/.include
  ./libs/librt/src/rtelm/light
  ./libs/librt/src/rtelm/plane
  ./libs/librt/src/rtelm/sphere
  ./libs/librt/src/rtelm/cylinder
  ./libs/librt/src/rtelm/utils
  ./libs/librt/src/rterr
  ./libs/librt/src/rtmth/equations
  ./libs/librt/src/rtmth/matrix
  ./libs/librt/src/rtmth/raytracing
  ./libs/librt/src/rtmth/vector
  ./libs/librt/src/rtmlx
  ./libs/librt/include
  ./libs/librt/libs/libft/include
  ./libs/librt/libs/libft/src
  ./include
)

run_norm() {
  for dir in "${NORM_DIRS[@]}"; do
    echo -e "${BLUE}===== $dir =====${RESET}"
    if [ ! -d "$dir" ]; then
      echo "  [skipped - directory not found]"
      continue
    fi
    mapfile -t files < <(find "$dir" -maxdepth 1 -type f \( -name "*.c" -o -name "*.h" \))
    if [ ${#files[@]} -eq 0 ]; then
      echo "  [no .c or .h files]"
      echo ""
      continue
    fi
    norminette "${files[@]}" | while IFS= read -r line; do
      if echo "$line" | grep -q "^Error:"; then
        continue
      elif echo "$line" | grep -q ": OK"; then
        echo -e "${GREEN}$line${RESET}"
      elif echo "$line" | grep -q ": Error"; then
        echo -e "${RED}$line${RESET}"
	  elif echo "$line" | grep -q "^Notice:"; then
  		echo -e "${YELLOW}$(echo "$line" | sed 's/(.*//')${RESET}"
      else
        echo "$line"
      fi
    done
    echo ""
  done
}

# Parse flags
if [ "$1" == "-norm" ]; then
  NORM=1
  shift
  RESOLUTION=$1
fi

if [ -z "$RESOLUTION" ] && [ "$NORM" -eq 0 ]; then
  echo "Usage: $0 [-norm] [DK, 2K, 4K, V]"
  exit 1
fi

if [ "$NORM" -eq 1 ]; then
  run_norm
  if [ -z "$RESOLUTION" ]; then
    exit 0
  fi
fi

if [ "$RESOLUTION" == "DK" ]; then
  RES="make W_WIDTH=1920 W_HEIGHT=1080"
elif [ "$RESOLUTION" == "2K" ]; then
  RES="make W_WIDTH=2560 W_HEIGHT=1440"
elif [ "$RESOLUTION" == "4K" ]; then
  RES="make W_WIDTH=3840 W_HEIGHT=2160"
elif [ "$RESOLUTION" == "V" ]; then
  RES="make W_WIDTH=300 W_HEIGHT=300"
  VALGRIND=1
else
  echo "Usage: $0 [-norm] [DK, 2K, 4K, V]"
  exit 1
fi

make fclean
eval $RES
make clean

for f in .test_files/mandatory/*.rt .test_files/mandatory/*/*.rt; do
  echo "Running $f"
  if [ "$VALGRIND" -eq 1 ]; then
    valgrind --leak-check=full --error-exitcode=1 ./miniRT "$f" 2>> $OP_FILE || echo "❌ crash or error: $f"
  else
    ./miniRT "$f" || echo "❌ crash or error: $f"
  fi
done

make fclean