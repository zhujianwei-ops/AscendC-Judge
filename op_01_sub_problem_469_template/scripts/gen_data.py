import numpy as np
import os
import sys

try:
    from ml_dtypes import bfloat16
except ImportError:
    bfloat16 = None

sys.path.insert(0, os.path.dirname(__file__))
from sub import impl

os.makedirs("input", exist_ok=True)
os.makedirs("output", exist_ok=True)


# --- Case 0 ---
np.random.seed(42 + 0)
os.makedirs("input/case0", exist_ok=True)
x = np.random.uniform(low=1, high=10, size=(8, 2048)).astype(np.float32)
x.tofile("input/case0/x.bin")
y = np.random.uniform(low=1, high=10, size=(8, 2048)).astype(np.float32)
y.tofile("input/case0/y.bin")



os.makedirs("output/golden_case0", exist_ok=True)
golden = impl(x, y)
if golden is not None:
    golden.tofile("output/golden_case0/golden_z.bin")

print(f"Generated test data and golden output for 1 cases.")
