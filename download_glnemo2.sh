#!/bin/bash
wget https://projets.lam.fr/attachments/download/13746/glnemo2-1.21.0.ubuntu20.04.x86_64.deb
apt-get update -y
apt-get install -y ./glnemo2-1.21.0.ubuntu20.04.x86_64.deb
apt-get clean
rm -rf /var/lib/apt/lists/*
