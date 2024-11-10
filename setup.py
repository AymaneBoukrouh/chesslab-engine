import glob

from setuptools import Extension
from setuptools import setup

engine_module = Extension(
    "chesslab_engine",
    sources=glob.glob("wrappers/*.cpp") + glob.glob("src/*.cpp"),
    include_dirs=["include"],
)

setup(name="chesslab_engine", version="1.0", ext_modules=[engine_module])
