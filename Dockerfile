FROM ubuntu:22.04

WORKDIR /workspace

RUN apt update && apt install -y grub-pc-bin xorriso

RUN mkdir -p /workspace/iso/boot/grub

COPY kfs-1.bin /workspace/iso/boot/kfs-1.bin
COPY grub.cfg /workspace/iso/boot/grub/grub.cfg

CMD ["grub-mkrescue", "-o", "/workspace/output/kfs-1.iso", "iso"]
