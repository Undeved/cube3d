#!/bin/bash

# Python environment setup for goinfre
VENV_PATH="/goinfre/$USER/python_env/venv"
CACHE_PATH="/goinfre/$USER/python_cache"

# Create directories if they don't exist
mkdir -p $CACHE_PATH
mkdir -p /goinfre/$USER/python_env

# Check if virtual environment exists, if not create it
if [ ! -d "$VENV_PATH" ]; then
    echo "Creating virtual environment in goinfre..."
    python3 -m venv $VENV_PATH
fi

# Activate virtual environment
echo "Activating virtual environment..."
source $VENV_PATH/bin/activate

# Set cache directories
export PIP_CACHE_DIR=$CACHE_PATH
export PYTHONPYCACHEPREFIX=$CACHE_PATH/__pycache__

# Create pycache directory if it doesn't exist
mkdir -p $CACHE_PATH/__pycache__

echo "Python environment is ready in goinfre!"
echo "Virtual environment: $VENV_PATH"
echo "Cache location: $CACHE_PATH"