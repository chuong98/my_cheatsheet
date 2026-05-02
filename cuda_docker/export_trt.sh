DOCKER_IMG="nvcr.io/nvidia/tensorrt:26.03-py3"
DOCKER_WORKDIR="/workspace"
ONNX_PATH=$DOCKER_WORKDIR"/weights/onnx_ckpt.onnx"
TRT_PATH=$DOCKER_WORKDIR"/weights/s2m2/trt"
docker run --gpus all -it --rm \
    -v $(pwd):$DOCKER_WORKDIR \
    -w $DOCKER_WORKDIR $DOCKER_IMG bash -c "python export_trt.py $ONNX_PATH --trt_path $TRT_PATH --precision fp16"
