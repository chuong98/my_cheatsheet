import argparse

from ultralytics import YOLO

def export_to_trt(args):
    # 1. Load the YOLOv11 model
    print("Loading model...")
    model = YOLO(args.ckpt)

    # 2. Export directly to TensorRT Engine
    # nms=True: Adds EfficientNMS plugin to the engine
    print("Exporting to TensorRT (this may take a few minutes)...")
    engine_path = model.export(
        format="engine",
        half=True,        # FP16 Precision
        dynamic=False,    # Static input shape
        simplify=True,    # Simplify ONNX graph
        nms=args.nms,     # <--- Includes NMS in the engine
        imgsz=[576, 960],        # Input size
        batch=1,
        device=0          # GPU Device ID
    )
    
    print(f"\nExport success! Engine saved at: {engine_path}")

def export_to_onnx(args):
    # 1. Load the YOLOv11 model
    print("Loading model...")
    model = YOLO(args.ckpt)

    # 2. Export to ONNX format
    print("Exporting to ONNX (this may take a few minutes)...")
    onnx_path = model.export(
        format="onnx",
        half=True,        # FP16 Precision
        dynamic=False,    # Static input shape
        simplify=True,    # Simplify ONNX graph
        nms=args.nms,     # <--- Exclude NMS from the ONNX model
        imgsz=[576, 960], # Input size
        batch=1,
        device=0          # GPU Device ID
    )
    
    print(f"\nExport success! ONNX model saved at: {onnx_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Export YOLO checkpoint to ONNX and/or TensorRT")
    parser.add_argument(
        "ckpt",
        type=str,
        help="Path to input PyTorch checkpoint (.pt)",
    )
    parser.add_argument(
        "--onnx",
        action="store_true",
        help="Export ONNX model",
    )
    parser.add_argument(
        "--trt",
        action="store_true",
        help="Export TensorRT engine",
    )
    parser.add_argument(
        "--nms",
        action="store_true",
        help="Include NMS in the exported model (only for TensorRT)",
    )
    args = parser.parse_args()

    # If no format is selected, keep the original behavior and export both.
    export_onnx = args.onnx or (not args.onnx and not args.trt)
    export_trt = args.trt or (not args.onnx and not args.trt)

    if export_trt:
        export_to_trt(args)
    if export_onnx:
        export_to_onnx(args)
