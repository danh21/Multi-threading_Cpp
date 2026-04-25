#!/bin/bash

WORKSPACE="."
OUTPUT_BIN="./out"

echo "🔍 Finding all .cpp files..."

find "$WORKSPACE" -name "*.cpp" | while read -r file; do
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "📄 Processing: $file"

    # ── Compile ───────────────────────────────
    compile_error=$(g++ "$file" -o "$OUTPUT_BIN" 2>&1)
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

    # ── Check if output block already exists ──
    if grep -q "=== OUTPUT ===" "$file"; then
        echo "⚠️  Output block exists, replacing..."
        # Remove old output block (from /* === OUTPUT === to end)
        sed -i '/\/\* === OUTPUT ===/,/\*\//{ /\/\* === OUTPUT ===/!{ /\*\//!d }; /\/\* === OUTPUT ===/d; /\*\//d }' "$file"
        # Remove trailing empty lines
        sed -i 's/[[:space:]]*$//' "$file"
    fi

    # ── Append output as comment block ────────
    timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    cat >> "$file" << EOF
/* === OUTPUT ===
 * Compiled : $timestamp
 * Command  : g++ $file -o out && ./out
 *
$(echo "$output" | sed 's/^/ * /')
 */
EOF

    echo "💾 Output appended to: $file"

done

# Cleanup
rm -f "$OUTPUT_BIN"
echo ""
echo "🎉 All files processed!"