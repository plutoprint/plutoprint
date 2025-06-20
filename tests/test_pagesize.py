import plutoprint
import pytest

def test_pagesize_new():
    assert plutoprint.PageSize()     == plutoprint.PageSize(0, 0)
    assert plutoprint.PageSize(1)    == plutoprint.PageSize(1, 1)
    assert plutoprint.PageSize(1, 2) == plutoprint.PageSize(1, 2)

    with pytest.raises(TypeError):
        plutoprint.PageSize(1, 2, 3)

def test_pagesize_repr():
    assert repr(plutoprint.PageSize())     == "plutoprint.PageSize(0, 0)"
    assert repr(plutoprint.PageSize(1))    == "plutoprint.PageSize(1, 1)"
    assert repr(plutoprint.PageSize(1, 2)) == "plutoprint.PageSize(1, 2)"

def test_pagesize_landscape():
    assert plutoprint.PageSize(1, 2).landscape() == plutoprint.PageSize(2, 1)
    assert plutoprint.PageSize(2, 1).landscape() == plutoprint.PageSize(2, 1)
    assert plutoprint.PageSize(2, 2).landscape() == plutoprint.PageSize(2, 2)

def test_pagesize_portrait():
    assert plutoprint.PageSize(2, 1).portrait() == plutoprint.PageSize(1, 2)
    assert plutoprint.PageSize(1, 2).portrait() == plutoprint.PageSize(1, 2)
    assert plutoprint.PageSize(2, 2).portrait() == plutoprint.PageSize(2, 2)

def test_pagesize_sequence():
    size = plutoprint.PageSize(1, 2)

    assert size[0] == 1
    assert size[1] == 2

    with pytest.raises(IndexError):
        size[2]

    assert len(plutoprint.PageSize())     == 2
    assert len(plutoprint.PageSize(1))    == 2
    assert len(plutoprint.PageSize(1, 2)) == 2

def test_pagesize_richcompare():
    a = plutoprint.PageSize(1, 2)
    b = plutoprint.PageSize(1, 2)
    c = plutoprint.PageSize(2, 1)

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

def test_pagesize_members():
    size = plutoprint.PageSize(1, 2)

    assert size.width  == 1
    assert size.height == 2

    with pytest.raises(AttributeError):
        size.width = 3
    with pytest.raises(AttributeError):
        size.height = 4

def test_pagesize_constants():
    assert plutoprint.PAGE_SIZE_NONE == plutoprint.PageSize()

    assert plutoprint.PAGE_SIZE_LETTER == plutoprint.PageSize(8.5 * plutoprint.UNITS_IN, 11 * plutoprint.UNITS_IN)
    assert plutoprint.PAGE_SIZE_LEGAL  == plutoprint.PageSize(8.5 * plutoprint.UNITS_IN, 14 * plutoprint.UNITS_IN)
    assert plutoprint.PAGE_SIZE_LEDGER == plutoprint.PageSize(11 * plutoprint.UNITS_IN, 17 * plutoprint.UNITS_IN)

    assert plutoprint.PAGE_SIZE_A3 == plutoprint.PageSize(297 * plutoprint.UNITS_MM, 420 * plutoprint.UNITS_MM)
    assert plutoprint.PAGE_SIZE_A4 == plutoprint.PageSize(210 * plutoprint.UNITS_MM, 297 * plutoprint.UNITS_MM)
    assert plutoprint.PAGE_SIZE_A5 == plutoprint.PageSize(148 * plutoprint.UNITS_MM, 210 * plutoprint.UNITS_MM)

    assert plutoprint.PAGE_SIZE_B4 == plutoprint.PageSize(250 * plutoprint.UNITS_MM, 353 * plutoprint.UNITS_MM)
    assert plutoprint.PAGE_SIZE_B5 == plutoprint.PageSize(176 * plutoprint.UNITS_MM, 250 * plutoprint.UNITS_MM)
