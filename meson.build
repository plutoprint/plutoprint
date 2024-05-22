project('plutoprint', 'c', 'cpp', version: '0.0.1', license: 'MIT')

python = import('python').find_installation(pure: false)

deps = [python.dependency()]
if not get_option('sdist')
    deps += dependency('plutobook', required: true)
endif

python.install_sources('__init__.py', subdir: 'plutoprint')
python.extension_module(
    'plutobook',
    'plutobook-module.c',
    dependencies: deps,
    subdir: 'plutoprint',
    install: true
)
