#!/bin/bash
echo "Requesting password to start docker service:"

# Staring docker service
sudo systemctl start docker

# Sign in to docker
docker login

# Downloading Debian image
docker pull alpine:latest

# Building project with control work #2
docker build -t cw2_kongdi .
