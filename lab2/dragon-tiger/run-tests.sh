#!/bin/bash

DTIGER=./src/driver/dtiger
TESTS=$(ls t/*.tig)

echo "1..$(echo "$TESTS" | wc -l)"
i=1

for test in $TESTS; do
    TEST_ARGS=$(grep '^# DTIGER-TEST:' "$test" | sed 's/# DTIGER-TEST: //')
    EXPECTED=$(grep '^# DTIGER-EXPECTED:' "$test" | sed 's/# DTIGER-EXPECTED: //')

    RESULT=$($DTIGER $TEST_ARGS "$test" 2>&1)

    if [ "$RESULT" = "$EXPECTED" ]; then
        echo "ok $i - $test"
    else
        echo "not ok $i - $test"
        echo "  ---"
        echo "  expected: '$EXPECTED'"
        echo "  got: '$RESULT'"
        echo "  ---"
    fi
    i=$((i+1))
done
