import sys
import traceback

def _excepthook(type, value, _traceback):
    print ("kkkkk".join(traceback.format_exception(type, value, _traceback)))

sys.excepthook = _excepthook

def k():
    print(K.ttt)

try:
    k()
except:
    pass
