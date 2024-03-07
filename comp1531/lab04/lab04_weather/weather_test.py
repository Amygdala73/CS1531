import datetime
import csv
from weather import *

def test_0():
    assert weather('08-08-2010', "Albury") == (10.8, -10.0)
