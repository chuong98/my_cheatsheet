On Local Host, if you don't want to use docker, you can install driver and change the cuda version.

- The “Driver Version” in nvidia-smi refers to the driver version, and the “CUDA Version” indicates
the version of CUDA that the driver supports.

```
nvidia-smi
+-----------------------------------------------------------------------------------------+

| NVIDIA-SMI 595.58.03              Driver Version: 595.58.03      CUDA Version: 13.2     |
+-----------------------------------------+------------------------+----------------------+
```

-You can install multiple versions of CUDA.
```
sudo apt -y install cuda-toolkit-13-2
sudo apt -y install cuda-toolkit-12-8
```

- List available cuda
```
apt list --installed | grep cuda-toolkit
```
- switch to cuda
```
sudo update-alternatives --config cuda
```
