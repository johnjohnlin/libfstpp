#!/bin/bash
set -e

# Default values
SKIP_HTML=false
SKIP_COMPILE=false
CHECK_THRESHOLDS=false
LINE_THRESHOLD=70
FUNC_THRESHOLD=73

# Argument parsing
while [[ "$#" -gt 0 ]]; do
    case $1 in
        --skip-html) SKIP_HTML=true ;;
        --skip-compile) SKIP_COMPILE=true ;;
        --check-thresholds) CHECK_THRESHOLDS=true ;;
        --line-threshold) LINE_THRESHOLD="$2"; shift ;;
        --func-threshold) FUNC_THRESHOLD="$2"; shift ;;
        *) echo "Unknown parameter passed: $1"; exit 1 ;;
    esac
    shift
done

# Directory definitions
WORKSPACE_ROOT=$(pwd)
BUILD_DIR="${WORKSPACE_ROOT}/build/debug"
SRC_DIR="${WORKSPACE_ROOT}/src"
OUTPUT_DIR="${WORKSPACE_ROOT}/coverage_report"

echo "========================================"
echo "    FST API Coverage Test Runner"
echo "========================================"
echo "Configuration:"
echo "  Skip HTML Report: $SKIP_HTML"
echo "  Check Thresholds: $CHECK_THRESHOLDS"
if [ "$CHECK_THRESHOLDS" = true ]; then
    echo "  Line Threshold:   $LINE_THRESHOLD%"
    echo "  Func Threshold:   $FUNC_THRESHOLD%"
fi
echo "========================================"

if [ "$SKIP_COMPILE" = false ]; then
    # Ensure build directory exists
    mkdir -p "$BUILD_DIR"

    echo "[1/5] Configuring CMake with coverage enabled..."
    cmake -S "$SRC_DIR" -B "$BUILD_DIR" -G Ninja -DENABLE_COVERAGE=ON

    echo "[2/5] Compiling..."
    ninja -C "$BUILD_DIR" all
else
    echo "[1/5] Skipping CMake configuration..."
    echo "[2/5] Skipping compilation..."
fi


echo "[3/5] Running tests..."
(cd "$BUILD_DIR" && ctest --output-on-failure)

echo "[4/5] Capturing and processing coverage data..."
# Capture everything
lcov --capture --directory "$BUILD_DIR" --output-file "$WORKSPACE_ROOT/coverage_full.info" --ignore-errors mismatch,inconsistent

# Filter: Clean up external and system files, keep only our target
echo "Filtering for files in fstapi/fstcpp..."
lcov --extract "$WORKSPACE_ROOT/coverage_full.info" "*/fstapi/fstcpp/*" --output-file "$WORKSPACE_ROOT/coverage.info"

if [ "$SKIP_HTML" = false ]; then
    echo "[5/5] Generating HTML report..."
    genhtml "$WORKSPACE_ROOT/coverage.info" --output-directory "$OUTPUT_DIR"
    echo "========================================"
    echo "Coverage report generated at:"
    echo "  $OUTPUT_DIR/index.html"
    echo "========================================"
else
    echo "[5/5] Skipping HTML report generation."
fi

if [ "$CHECK_THRESHOLDS" = true ]; then
    echo "Checking coverage thresholds..."
    lcov --summary "$WORKSPACE_ROOT/coverage.info" | python3 -c "
import sys, re

content = sys.stdin.read()
print(content)

line_match = re.search(r'lines\.+: (\d+\.\d+)%', content)
func_match = re.search(r'functions\.+: (\d+\.\d+)%', content)

if not line_match or not func_match:
    print('Could not parse coverage info.')
    sys.exit(1)

line_cov = float(line_match.group(1))
func_cov = float(func_match.group(1))

required_line = $LINE_THRESHOLD
required_func = $FUNC_THRESHOLD

print(f'Line Coverage: {line_cov}% (Required: {required_line}%)')
print(f'Function Coverage: {func_cov}% (Required: {required_func}%)')

if line_cov < required_line or func_cov < required_func:
    print('Coverage threshold not met!')
    sys.exit(1)
"
    if [ $? -ne 0 ]; then
        echo "Error: Coverage thresholds were not met."
        exit 1
    fi
fi
