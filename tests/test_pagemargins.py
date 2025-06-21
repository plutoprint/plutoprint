import plutoprint
import pytest

def test_pagemargins_new():
    assert plutoprint.PageMargins()           == plutoprint.PageMargins(0, 0, 0, 0)
    assert plutoprint.PageMargins(1)          == plutoprint.PageMargins(1, 1, 1, 1)
    assert plutoprint.PageMargins(1, 2)       == plutoprint.PageMargins(1, 2, 1, 2)
    assert plutoprint.PageMargins(1, 2, 3)    == plutoprint.PageMargins(1, 2, 3, 2)
    assert plutoprint.PageMargins(1, 2, 3, 4) == plutoprint.PageMargins(1, 2, 3, 4)

    with pytest.raises(TypeError):
        plutoprint.PageMargins(1, 2, 3, 4, 5)

def test_pagemargins_repr():
    assert repr(plutoprint.PageMargins())           == "plutoprint.PageMargins(0, 0, 0, 0)"
    assert repr(plutoprint.PageMargins(1))          == "plutoprint.PageMargins(1, 1, 1, 1)"
    assert repr(plutoprint.PageMargins(1, 2))       == "plutoprint.PageMargins(1, 2, 1, 2)"
    assert repr(plutoprint.PageMargins(1, 2, 3))    == "plutoprint.PageMargins(1, 2, 3, 2)"
    assert repr(plutoprint.PageMargins(1, 2, 3, 4)) == "plutoprint.PageMargins(1, 2, 3, 4)"

def test_pagemargins_sequence():
    margins = plutoprint.PageMargins(1, 2, 3, 4)

    assert margins[0] == 1
    assert margins[1] == 2
    assert margins[2] == 3
    assert margins[3] == 4

    with pytest.raises(IndexError):
        margins[4]

    assert len(plutoprint.PageMargins())           == 4
    assert len(plutoprint.PageMargins(1))          == 4
    assert len(plutoprint.PageMargins(1, 2))       == 4
    assert len(plutoprint.PageMargins(1, 2, 3))    == 4
    assert len(plutoprint.PageMargins(1, 2, 3, 4)) == 4

def test_pagemargins_richcompare():
    a = plutoprint.PageMargins(1, 2, 3, 4)
    b = plutoprint.PageMargins(1, 2, 3, 4)
    c = plutoprint.PageMargins(4, 3, 2, 1)

    assert a == b
    assert a != c

    with pytest.raises(TypeError):
        a < b
    with pytest.raises(TypeError):
        a <= b
    with pytest.raises(TypeError):
        a > b
    with pytest.raises(TypeError):
        a >= b

def test_pagemargins_members():
    margins = plutoprint.PageMargins(1, 2, 3, 4)

    assert margins.top    == 1
    assert margins.right  == 2
    assert margins.bottom == 3
    assert margins.left   == 4

    with pytest.raises(AttributeError):
        margins.top = 5
    with pytest.raises(AttributeError):
        margins.right = 6
    with pytest.raises(AttributeError):
        margins.bottom = 7
    with pytest.raises(AttributeError):
        margins.left = 8

def test_pagemargins_constants():
    assert plutoprint.PAGE_MARGINS_NONE == plutoprint.PageMargins(0, 0, 0, 0)

    assert plutoprint.PAGE_MARGINS_NORMAL == plutoprint.PageMargins(72, 72, 72, 72)
    assert plutoprint.PAGE_MARGINS_NARROW == plutoprint.PageMargins(36, 36, 36, 36)

    assert plutoprint.PAGE_MARGINS_MODERATE == plutoprint.PageMargins(72, 54, 72, 54)
    assert plutoprint.PAGE_MARGINS_WIDE     == plutoprint.PageMargins(72, 144, 72, 144)
