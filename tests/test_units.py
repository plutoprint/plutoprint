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
