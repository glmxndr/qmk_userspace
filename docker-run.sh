docker run -it --rm \
  -v "${PWD}/build:/app/qmk_firmware/.build" \
  -v "${PWD}:/app/qmk_userspace" \
  qmk:ubuntu-halcyon

