FROM ghcr.io/qmk/qmk_cli

RUN apt update && apt install curl -y
WORKDIR /usr/local/bin
RUN curl -fLO https://github.com/curl/wcurl/releases/latest/download/wcurl && chmod +x wcurl
RUN wcurl https://gitlab.com/glmxndr/scr/-/raw/main/scr && chmod +x scr
RUN echo "source <(scr --completions)" >> /root/.bashrc

# Set the default location for qmk_firmware
ENV QMK_HOME=/app/qmk_firmware
WORKDIR /app
RUN qmk setup -y -H /app/qmk_firmware
WORKDIR /app/qmk_userspace
RUN qmk config user.overlay_dir="$(realpath .)"

ENTRYPOINT ["bash"]
