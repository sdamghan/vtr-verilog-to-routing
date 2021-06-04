FROM gitpod/workspace-full

USER root
# Install util tools.
RUN apt-get update \
 && apt-get install -y \
  apt-utils \
  sudo \
  git \
  less \
  libfmt-dev \
  libspdlog-dev \
  lcov \
  binutils \
  binutils-gold \
  build-essential \
  flex \
  fontconfig \
  libcairo2-dev \
  libgtk-3-dev \
  libevent-dev \
  libfontconfig1-dev \
  liblist-moreutils-perl \
  libncurses5-dev \
  libx11-dev \
  libxft-dev \
  libxml++2.6-dev \
  python-lxml \
  qt5-default \
  wget \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*


# Give back control
USER root

# Cleaning
RUN apt-get clean
