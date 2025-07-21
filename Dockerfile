FROM ghcr.io/qmk/qmk_cli

# Set the default location for qmk_firmware
ENV QMK_HOME=/app/qmk_firmware
WORKDIR /app
RUN python3 -m pip install qmk
RUN qmk setup -y -H /app/qmk_firmware
WORKDIR /app/qmk_userspace
RUN qmk config user.overlay_dir="$(realpath .)"

ENTRYPOINT ["bash"]
