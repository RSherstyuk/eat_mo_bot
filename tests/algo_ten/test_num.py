from numpy.testing._private.utils import assert_array_equal

from src.eat_mo_bot.main import pynum
import numpy as np

def test_numpy():
    arr = np.linspace(0, 1, 100)
    f = np.sin(arr)
    test_f = pynum()
    for i in range(len(arr)):
        assert f[i] == test_f[i] 

    

