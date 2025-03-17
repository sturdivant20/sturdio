"""

SturdIO
======

Daniel Sturdivant's basic file reading/writing utilities

Contains the following modules:

1. `BinaryFile`
2. `YamlParser`
3. `iotools`

"""

from __future__ import annotations
from sturdio._sturdio_core import BinaryFile
from sturdio._sturdio_core import YamlParser
from sturdio._sturdio_core import iotools
from . import _sturdio_core

__all__: list = ["__doc__", "__version__", "BinaryFile", "YamlParser", "iotools"]
__version__: str = "1.0.0"
