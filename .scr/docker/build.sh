##== Document options here:
##opt: -x | file | X_FILE | Description
##opt: -y | flag | Y_FLAG | Description
##== Document positional arguments here:
##arg: srcFile | file | SRC_FILE | Description
##arg: destDir | dir  | DEST_DIR | Description
#== Tell what this subcommand does here:
#help: Add helpful description here.

docker buildx build . \
    -o type=docker \
    -t qmk:ubuntu-halcyon \
    --progress=plain 

