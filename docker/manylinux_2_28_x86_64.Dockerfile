FROM quay.io/pypa/manylinux_2_28_x86_64:latest

ENV PYTHON3=/opt/python/cp312-cp312/bin/python3
ENV PATH="/opt/python/cp312-cp312/bin:${PATH}"

RUN $PYTHON3 -m pip install --upgrade pip && \
    $PYTHON3 -m pip install meson ninja

RUN dnf install -y \
        libcurl-devel \
        libicu-devel \
        bzip2-devel \
        brotli-devel \
        gperf

RUN cd /tmp && \
    git clone https://github.com/plutoprint/plutobook.git && \
    cd plutobook && \
    meson setup build --prefix=/usr && \
    meson compile -C build && \
    meson install -C build --strip

RUN pkg-config --modversion plutobook
