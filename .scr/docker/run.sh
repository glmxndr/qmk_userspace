##== Document options here:
##opt: -x | file | X_FILE | Description
##opt: -y | flag | Y_FLAG | Description
##== Document positional arguments here:
##arg: srcFile | file | SRC_FILE | Description
##arg: destDir | dir  | DEST_DIR | Description
#== Tell what this subcommand does here:
#help: Add helpful description here.

docker run -it --rm \
  -v "${PWD}/build:/app/qmk_firmware/.build" \
  -v "${PWD}:/app/qmk_userspace" \
  qmk:ubuntu-halcyon
