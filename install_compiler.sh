#!/bin/bash
# Install cross-compiler 'i686-elf' 

echo "🚀 I will install cross-compiler, i686-elf..."

# create directory
mkdir -p /tmp/cross && cd /tmp/cross

# download zip file and unzup it
wget https://github.com/lordmilko/i686-elf-tools/releases/download/7.1.0/i686-elf-tools-linux.zip
unzip -q i686-elf-tools-linux.zip

echo 'export PATH="/tmp/cross/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc

# verify if it's installed correctly
if i686-elf-gcc --version >/dev/null 2>&1; then
    echo "✅ Installed successfully! with GCC version:"
    i686-elf-gcc --version | head -1
    echo "now run 'make kfs-1.bin'"
else
    echo "❌ Failed to install. check bin/ with: ls ~/opt/cross/bin/"
fi

