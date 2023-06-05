# ctypes_test.py
import ctypes
import os
import pathlib


TILED_BYTES_CLIB_NAME = "libTiledBytesShared.dll"
TILED_BYTES_CLIB_PATH = f"{os.path.dirname(__file__)}\{TILED_BYTES_CLIB_NAME}"
TILED_BYTES = ctypes.CDLL(TILED_BYTES_CLIB_PATH)

if TILED_BYTES:
    print("Loaded TiledBytes CLib")
else:
    TILED_BYTES = None
    print(f"Could not load {TILED_BYTES_CLIB_NAME} at '{TILED_BYTES_CLIB_PATH}'")


if __name__ == "__main__":
    if not TILED_BYTES:
        exit(1)

    print("Testing TiledBytes python wrapper.")
    print(f" + {TILED_BYTES}")
    print(f" + {vars(TILED_BYTES)}")
    
    print("---")
    print("")
    print("template<typename T> T load(const std::string& filepath)")
    print(TILED_BYTES.TbLoadTsx)