import plutoprint
import pytest

def test_units():
    assert isinstance(plutoprint.UNITS_PT, float)
    assert isinstance(plutoprint.UNITS_PC, float)
    assert isinstance(plutoprint.UNITS_IN, float)
    assert isinstance(plutoprint.UNITS_PX, float)
    assert isinstance(plutoprint.UNITS_CM, float)
    assert isinstance(plutoprint.UNITS_MM, float)

    assert plutoprint.UNITS_PT == pytest.approx(1.0)
    assert plutoprint.UNITS_PC == pytest.approx(12.0)
    assert plutoprint.UNITS_IN == pytest.approx(72.0)
    assert plutoprint.UNITS_PX == pytest.approx(72.0 / 96.0)
    assert plutoprint.UNITS_CM == pytest.approx(72.0 / 2.54)
    assert plutoprint.UNITS_MM == pytest.approx(72.0 / 25.4)

    assert 72.0 == pytest.approx(   1 * plutoprint.UNITS_IN)  # 1 inch = 72 pt
    assert 72.0 == pytest.approx(   6 * plutoprint.UNITS_PC)  # 6 picas = 72 pt
    assert 72.0 == pytest.approx(  72 * plutoprint.UNITS_PT)  # 72 points = 72 pt
    assert 72.0 == pytest.approx(  96 * plutoprint.UNITS_PX)  # 96 px = 72 pt
    assert 72.0 == pytest.approx(2.54 * plutoprint.UNITS_CM)  # 2.54 cm = 72 pt
    assert 72.0 == pytest.approx(25.4 * plutoprint.UNITS_MM)  # 25.4 mm = 72 pt

    assert  1.0 == pytest.approx(72.0 / plutoprint.UNITS_IN)  # 72 pt = 1 inch
    assert  6.0 == pytest.approx(72.0 / plutoprint.UNITS_PC)  # 72 pt = 6 picas
    assert 72.0 == pytest.approx(72.0 / plutoprint.UNITS_PT)  # 72 pt = 72 points
    assert 96.0 == pytest.approx(72.0 / plutoprint.UNITS_PX)  # 72 pt = 96 px
    assert 2.54 == pytest.approx(72.0 / plutoprint.UNITS_CM)  # 72 pt = 2.54 cm
    assert 25.4 == pytest.approx(72.0 / plutoprint.UNITS_MM)  # 72 pt = 25.4 mm
