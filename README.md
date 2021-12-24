A simple implementation/library of TensorFloat32 for precision evaluation.
---------------------------------

TensorFloat-32, or TF32, is the new math mode in NVIDIA A100 GPUs.
TF32 uses the same 10-bit mantissa as the half-precision (FP16) math, shown to have more than sufficient margin for the precision requirements of AI workloads. And TF32 adopts the same 8-bit exponent as FP32 so it can support the same numeric range.
It is technically a 19-bit format. You can treat it as an extended-precision BFLOAT16, say “BFLOAT19" ☺ Or like reduced-precision FP32.
So, TF32 has:
 - 1 bit sign
 - 8 bits exponent
 - 10 bits fraction

The advantage of TF32 is that the format is the same as FP32. When computing inner products with TF32, the input operands have their mantissas rounded from 23 bits to 10 bits. The rounded operands are multiplied exactly, and accumulated in normal FP32.
TF32 Tensor Cores operate on FP32 inputs and produce results in FP32 with no code change required. Non-matrix operations continue to use FP32. This provides an easy path to accelerate FP32 input/output data in DL frameworks and HPC.

*Range:* ~1.18e-38 … ~3.40e38 with 4 significant decimal digits precision.
*Usage:*
 - The big advantage of TF32 is that compiler support is required only at the deepest levels, i.e. inside the CUDA compiler. The rest of code just sees FP32 with less precision, but the same dynamic range. Exploiting TF32 will largely be a matter of tweaking callers of libraries to indicate whether TF32 is okay. TF32 exists as something that can be quickly plugged in to exploit Tensor Core speed without much work.
 - Formats such as FP16 and BFLOAT16 require more work, since they involve different bit layouts. It is worth putting in efforts into using these formats, since they reduce memory bandwidth and consequently permit even faster execution.

For comparison, A100’s peak performances are:
 - FP32 without tensor core: 19.5 TFLOPS
 - TF32 tensor core: 156 TFLOPS (so, using TF32 in place of FP32 can give you an easy speed improvement).
 - FP16/BF16 tensor core: 312 TFLOPS (so, thoughtfully designed switch to FP16/BF16 can give you more speed improvements, but the costs are higher).

