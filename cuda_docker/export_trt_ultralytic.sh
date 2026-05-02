DOCKER_IMG="ultralytics:trt10.16.0.72"
DOCKER_WORKDIR="/workspace"
WEIGHTS_DIR="/home/chuong/Workspace/cctracker_cpp/weights"
CKPT_PATH="/weights/murata_2404_best.pt"

DOCKERFILE_PATH="docker/Dockerfile"

if ! docker image inspect "$DOCKER_IMG" >/dev/null 2>&1; then
    echo "Docker image '$DOCKER_IMG' not found. Building from $DOCKERFILE_PATH..."
    docker build -t "$DOCKER_IMG" -f "$DOCKERFILE_PATH" .
fi

docker run --gpus all -it --rm \
    -v "$PWD":"$DOCKER_WORKDIR" \
    -v $WEIGHTS_DIR:/weights \
    -w "$DOCKER_WORKDIR" "$DOCKER_IMG" bash -c "python export_ultralytic.py $CKPT_PATH --onnx --trt"
