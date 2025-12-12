#!/bin/bash

# Vendors pyprima from https://github.com/nbelakovski/prima

set -o nounset
set -o errexit

REPO_URL="https://github.com/nbelakovski/prima"
COMMIT_HASH="bb031b16d44bea925dd84ca241b13279d8b121f7"

ROOT_DIR="prima"

rm -rf $ROOT_DIR
mkdir $ROOT_DIR
git clone $REPO_URL $ROOT_DIR
cd $ROOT_DIR
git checkout $COMMIT_HASH
rm -rf .development
rm -rf .git
rm .gitmodules
rm -rf benchmark/
rm -rf fortran/
rm -rf matlab/
rm -rf c/
rm -rf python/

echo "Update this directory using vendor_pyprima.sh" >$ROOT_DIR/README.md
