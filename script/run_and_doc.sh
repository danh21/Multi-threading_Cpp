#!/bin/bash

WORKSPACE="."
OUTPUT_BIN="./out"

echo "🔍 Finding all .cpp files..."

find "$WORKSPACE" -name "*.cpp" | while read -r file; do
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "📄 Processing: $file"

    # ── Compile ───────────────────────────────
    compile_error=$(g++ "$file" -o "$OUTPUT_BIN" -std=c++23 -lpthread 2>&1)
    if [ $? -ne 0 ]; then
        echo "❌ Compile error: $file"
        echo "$compile_error"
        continue
    fi

    # ── Run ───────────────────────────────────
    output=$(timeout 10 "$OUTPUT_BIN" 2>&1)
    exit_code=$?

    if [ $exit_code -eq 124 ]; then
        output="[TIMEOUT] Program exceeded 10 seconds"
        echo "⏱️  Timeout: $file"
    else
        echo "✅ Done: $file"
    fi

    # ── Replace or append output block ────────
    if grep -q "=== OUTPUT ===" "$file"; then
        echo "⚠️  Output block exists, replacing..."

        # Get line number of OUTPUT marker
        marker_line=$(grep -n "/\* === OUTPUT ===" "$file" | head -1 | cut -d: -f1)

        # Keep only lines before marker
        head -n $((marker_line - 1)) "$file" > "$file.tmp"
    else
        cp "$file" "$file.tmp"
    fi

    # Strip trailing blank lines using awk
    # Buffer blank lines, only print if followed by non-blank content
    # → trailing blanks at EOF are discarded
    awk '/^[[:space:]]*$/{p=p"\n"; next} {printf "%s",p; p=""; print}' "$file.tmp" > "$file"
    rm -f "$file.tmp"

    # Append output block — exactly 1 blank line before
    {
        printf "\n/* === OUTPUT ===\n"
        printf " * Command  : g++ %s -o out -std=c++23 -lpthread && ./out\n" "$file"
        printf " *\n"
        echo "$output" | sed 's/^/ * /'
        printf " */"
    } >> "$file"

    echo "💾 Output appended to: $file"

done

# Cleanup
rm -f "$OUTPUT_BIN"
echo ""
echo "🎉 All files processed!"