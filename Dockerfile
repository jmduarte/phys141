FROM ucsdets/scipy-ml-notebook:2023.2-stable

LABEL maintainer="Javier Duarte <jduarte@ucsd.edu>"

USER root

# Install tcsh xorg-dev gfortran emacs
RUN apt-get update -y && \
    apt-get install --no-install-recommends -y \
    libtinfo5 tcsh xorg-dev gfortran g++ man emacs ffmpeg imagemagick && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY run_jupyter.sh /
RUN chmod +x /run_jupyter.sh

# Install nemo
RUN wget https://teuben.github.io/nemo/install_nemo
SHELL ["/bin/tcsh", "-c", "source install_nemo nemo=nemo glnemo=1 ubuntu=1"]

# Run env
RUN chmod +x nemo/nemo_start.sh

RUN mamba install -y -c conda-forge \
    cupy

# Fix permissions
RUN fix-permissions /home/$NB_USER

USER $NB_UID:$NB_GID

CMD ["nemo/nemo_start.sh && start-notebook.sh"]
