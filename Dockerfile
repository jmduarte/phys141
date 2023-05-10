FROM ucsdets/scipy-ml-notebook:2023.2-stable

LABEL maintainer="Javier Duarte <jduarte@ucsd.edu>"

USER root

# Install tcsh xorg-dev gfortran emacs glnemo2
RUN apt-get update -y && \
    apt-get install --no-install-recommends -y \
    libtinfo5 tcsh xorg-dev gfortran g++ man emacs ffmpeg imagemagick qt5-default libqt5gui5 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Download glnemo2
COPY download_glnemo2.sh /home/$NB_USER/download_glnemo2.sh
RUN source download_glnemo2.sh

COPY run_jupyter.sh /
RUN chmod +x /run_jupyter.sh

# Install nemo
COPY install_nemo /home/$NB_USER/install_nemo
SHELL ["/bin/tcsh", "-c", "source install_nemo nemo=nemo glnemo=1 ubuntu=1"]

# Run env
RUN chmod +x nemo/nemo_start.sh

RUN mamba install -y -c conda-forge \
    cupy

RUN pip install nbconvert[qtpdf,webpdf]==7.2.1

# Fix permissions
RUN fix-permissions /home/$NB_USER

USER $NB_UID:$NB_GID

# CMD ["nemo/nemo_start.sh && start-notebook.sh"]
