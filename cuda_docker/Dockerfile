FROM ultralytics/ultralytics:latest-export

# Since we use Docker TensorRT image nvcr.io/nvidia/tensorrt:26.03-py3,
# which use tensor rt 10.16.0.72, we update the docker image manually

RUN pip install tensorrt==10.16.0.72
