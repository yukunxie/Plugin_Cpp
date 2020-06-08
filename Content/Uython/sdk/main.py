# -*- coding: utf-8 -*-

print("Uython: load main", flush=True)

import sys
import traceback
import Uython

sys.stderr.line_buffering = False

def _excepthook(type, value, _traceback):
    Uython.print_error ("zzzzzzzzzzz".join(traceback.format_exception(type, value, _traceback)))
sys.excepthook = _excepthook

def k():
    print(K.ttt)

k()

