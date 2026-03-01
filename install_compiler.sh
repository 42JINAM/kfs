#!/bin/bash
# i686-elf 크로스 컴파일러 자동 설치 (sudo 없이)

echo "🚀 i686-elf 크로스 컴파일러 설치 시작..."

# 디렉토리 생성
mkdir -p /tmp/cross && cd /tmp/cross

# zip 다운로드 & 압축 해제
wget https://github.com/lordmilko/i686-elf-tools/releases/download/7.1.0/i686-elf-tools-linux.zip
unzip -q i686-elf-tools-linux.zip

echo 'export PATH="/tmp/cross/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc  # 현재 셸 갱신
export PATH="/tmp/cross/bin:$PATH"

# 확인
if i686-elf-gcc --version >/dev/null 2>&1; then
    echo "✅ 설치 완료! GCC 버전:"
    i686-elf-gcc --version | head -1
    echo "이제 'make kfs-1.bin' 실행하세요!"
else
    echo "❌ 설치 실패. bin/ 폴더 확인: ls ~/opt/cross/bin/"
fi

