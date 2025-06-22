import plutoprint
import pytest

def test_resourcedata_new():
    assert isinstance(plutoprint.ResourceData(b'Hello World'), plutoprint.ResourceData)

    with pytest.raises(TypeError):
        plutoprint.ResourceData()

    assert isinstance(plutoprint.ResourceData('Hello World'),  plutoprint.ResourceData)
    assert isinstance(plutoprint.ResourceData('Hello World', 'text/plain'),  plutoprint.ResourceData)
    assert isinstance(plutoprint.ResourceData('Hello World', 'text/plain', 'utf8'), plutoprint.ResourceData)
    assert isinstance(plutoprint.ResourceData('Hello World', mime_type='text/plain', text_encoding='utf8'), plutoprint.ResourceData)

@pytest.fixture
def resource():
    return plutoprint.ResourceData('Hello World', 'text/plain', 'utf8')

def test_resource_get_content(resource):
    assert isinstance(resource.get_content(), memoryview)
    assert resource.get_content() == b'Hello World'

def test_resource_get_mime_type(resource):
    assert isinstance(resource.get_mime_type(), str)
    assert resource.get_mime_type() == 'text/plain'

def test_resource_get_text_encoding(resource):
    assert isinstance(resource.get_text_encoding(), str)
    assert resource.get_text_encoding() == 'utf8'
