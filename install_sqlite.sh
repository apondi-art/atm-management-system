#!/bin/bash
# Set SQLite version (Check for latest at https://www.sqlite.org/download.html)
SQLITE_VERSION="3450000" # Updated to latest version as of early 2024
SQLITE_URL="https://www.sqlite.org/2024/sqlite-amalgamation-${SQLITE_VERSION}.zip"
DOWNLOAD_DIR="/tmp"
TARGET_DIR="./sqlite"

# Function for error handling
error_exit() {
    echo "❌ Error: $1" >&2
    exit 1
}

# Verbose logging
set -x

# Step 1: Download SQLite
echo "📥 Downloading SQLite from $SQLITE_URL..."
wget --show-progress --tries=3 "$SQLITE_URL" -O "$DOWNLOAD_DIR/sqlite.zip" || error_exit "SQLite download failed"

# Verify download success
[ -f "$DOWNLOAD_DIR/sqlite.zip" ] || error_exit "Download file not found"

# Step 2: Extract the ZIP file
echo "📂 Extracting SQLite..."
unzip -q "$DOWNLOAD_DIR/sqlite.zip" -d "$DOWNLOAD_DIR/sqlite_extracted" || error_exit "Extraction failed"

# Find the extracted folder dynamically
EXTRACTED_DIR=$(find "$DOWNLOAD_DIR/sqlite_extracted" -maxdepth 1 -type d -name "sqlite-amalgamation-*")

# Verify extraction success
[ -n "$EXTRACTED_DIR" ] || error_exit "No extracted directory found"

# Step 3: Move sqlite3.c and sqlite3.h
mkdir -p "$TARGET_DIR"
mv "$EXTRACTED_DIR/sqlite3.c" "$TARGET_DIR/" || error_exit "Failed to move sqlite3.c"
mv "$EXTRACTED_DIR/sqlite3.h" "$TARGET_DIR/" || error_exit "Failed to move sqlite3.h"

echo "✅ SQLite files moved to $TARGET_DIR/"

# Step 4: Clean up
echo "🧹 Cleaning up..."
rm -rf "$DOWNLOAD_DIR/sqlite_extracted"
rm "$DOWNLOAD_DIR/sqlite.zip"

echo "🎉 SQLite3 setup completed successfully!"