#!/bin/bash

echo "Running comprehensive parser tests..."
echo "===================================="

# Test files array
test_files=(
    "test_basic_class.txt"
    "test_multiple_inheritance.txt"
    "test_arrays.txt"
    "test_implementation.txt"
    "test_functions.txt"
    "test_expressions.txt"
    "test_control_structures.txt"
    "test_method_calls.txt"
    "test_nested_calls.txt"
    "test_empty_constructs.txt"
    "test_comprehensive.txt"
    "test_arithmetic.txt"
    "test_edge_cases.txt"
)

# Compile the parser
echo "Compiling parser..."
bison -d parser.y
flex lexer.l
gcc -o parser lex.yy.c parser.tab.c -lm

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

echo "Parser compiled successfully!"
echo ""

# Run tests
passed=0
total=0

for test_file in "${test_files[@]}"; do
    echo "Testing: $test_file"
    echo "------------------------"

    if [ -f "$test_file" ]; then
        ./parser "$test_file" > test_output.tmp 2>&1
        if [ $? -eq 0 ]; then
            echo "✓ PASSED"
            ((passed++))
        else
            echo "✗ FAILED"
            echo "Error output:"
            cat test_output.tmp
        fi
    else
        echo "✗ FILE NOT FOUND"
    fi

    ((total++))
    echo ""
done

# Cleanup
rm -f test_output.tmp

echo "Test Results: $passed/$total tests passed"

if [ $passed -eq $total ]; then
    echo "🎉 All tests passed!"
else
    echo "⚠️  Some tests failed"
fi
