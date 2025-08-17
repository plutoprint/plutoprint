import plutoprint
import pytest

def test_resource_fetcher():
    fetcher = plutoprint.ResourceFetcher()

    with pytest.raises(plutoprint.Error):
        fetcher.fetch_url(str())

def test_default_resource_fetcher(tmp_path):
    with pytest.raises(TypeError):
        plutoprint.DefaultResourceFetcher()

    assert isinstance(plutoprint.default_resource_fetcher, plutoprint.ResourceFetcher)

    path = tmp_path / "hello.txt"
    path.write_text("Hello World")

    with pytest.raises(plutoprint.Error):
        plutoprint.default_resource_fetcher.fetch_url(path.resolve().as_posix())

    resource = plutoprint.default_resource_fetcher.fetch_url(path.resolve().as_uri())

    assert isinstance(resource, plutoprint.ResourceData)
    assert resource.get_content() == b'Hello World'
    assert resource.get_mime_type() == 'text/plain'
