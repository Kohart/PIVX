#!/bin/sh

# Install libdb4.8 (Berkeley DB).

export LC_ALL=C
set -e

if [ -z "${1}" ]; then
  echo "Usage: $0 <base-dir> [<ci-mode>] [<extra-bdb-configure-flag> ...]"
  echo
  echo "Must specify a single argument: the directory in which db4 will be built."
  echo "This is probably \`pwd\` if you're at the root of the pivx repository."
  exit 1
fi

expand_path() {
  cd "${1}" && pwd -P
}

if [ "$#" -ge 2 ]; then
  if [ "${2}" != 'true' ]; then
    BDB_PREFIX="$(expand_path ${1})/db4"; shift;
    echo "Installing in user mode..."
  else
    BDB_PREFIX="$(expand_path ${1})"; shift; shift;
    echo "Installing in CI mode..."
  fi
fi
BDB_VERSION='db-4.8.30.NC'
BDB_HASH='12edc0df75bf9abd7f82f821795bcee50f42cb2e5f76a6a281b85732798364ef'
BDB_URL="https://download.oracle.com/berkeley-db/${BDB_VERSION}.tar.gz"

check_exists() {
  command -v "$1" >/dev/null 2>&1
}

sha256_check() {
  # Args: <sha256_hash> <filename>
  #
  if check_exists sha256sum; then
    echo "${1}  ${2}" | sha256sum -c
  elif check_exists sha256; then
    if [ "$(uname)" = "FreeBSD" ]; then
      sha256 -c "${1}" "${2}"
    else
      echo "${1}  ${2}" | sha256 -c
    fi
  else
    echo "${1}  ${2}" | shasum -a 256 -c
  fi
}

http_get() {
  # Args: <url> <filename> <sha256_hash>
  #
  # It's acceptable that we don't require SSL here because we manually verify
  # content hashes below.
  #
  if [ -f "${2}" ]; then
    echo "File ${2} already exists; not downloading again"
  elif check_exists curl; then
    curl --insecure --retry 5 "${1}" -o "${2}"
  else
    wget --no-check-certificate "${1}" -O "${2}"
  fi

  sha256_check "${3}" "${2}"
}

mkdir -p "${BDB_PREFIX}"
http_get "${BDB_URL}" "${BDB_VERSION}.tar.gz" "${BDB_HASH}"
tar -xzf ${BDB_VERSION}.tar.gz -C "$BDB_PREFIX"
cd "${BDB_PREFIX}/${BDB_VERSION}/"

# Apply a patch necessary when building with clang and c++11 (see https://community.oracle.com/thread/3952592)
CLANG_CXX11_PATCH_URL='https://gist.githubusercontent.com/LnL7/5153b251fd525fe15de69b67e63a6075/raw/7778e9364679093a32dec2908656738e16b6bdcb/clang.patch'
CLANG_CXX11_PATCH_HASH='7a9a47b03fd5fb93a16ef42235fa9512db9b0829cfc3bdf90edd3ec1f44d637c'
http_get "${CLANG_CXX11_PATCH_URL}" clang.patch "${CLANG_CXX11_PATCH_HASH}"
patch -p2 < clang.patch

BIGSUR_PATCH_URL='https://gist.githubusercontent.com/Fuzzbawls/51f8cc35e03d18f35b82e7b36e66491d/raw/d57f6731def206db65191932f5ae7016a325fde5/configure-pre-0.4.2.418-big_sur.diff'
BIGSUR_PATCH_HASH='83af02f2aa2b746bb7225872cab29a253264be49db0ecebb12f841562d9a2923'
http_get "${BIGSUR_PATCH_URL}" bigsur.patch "${BIGSUR_PATCH_HASH}"
patch dist/configure < bigsur.patch

# The packaged config.guess and config.sub are ancient (2009) and can cause build issues.
# Replace them with modern versions.
# See https://github.com/bitcoin/bitcoin/issues/16064
CONFIG_GUESS_URL='https://gist.githubusercontent.com/Fuzzbawls/8b1a7c9d094e3dcb3295cf7c56e35bc5/raw/e357876828a4e2f263b184bc7cb7ea2322b540a9/config.guess'
CONFIG_GUESS_HASH='e3d148130e9151735f8b9a8e69a70d06890ece51468a9762eb7ac0feddddcc2f'
CONFIG_SUB_URL='https://gist.githubusercontent.com/Fuzzbawls/db174c45f41e77862184ff05f8055942/raw/9c3965804b7376ec371a4cbfc851be96f3f38a3d/config.sub'
CONFIG_SUB_HASH='11c54f55c3ac99e5d2c3dc2bb0bcccbf69f8223cc68f6b2438daa806cf0d16d8'

rm -f "dist/config.guess"
rm -f "dist/config.sub"

http_get "${CONFIG_GUESS_URL}" dist/config.guess "${CONFIG_GUESS_HASH}"
http_get "${CONFIG_SUB_URL}" dist/config.sub "${CONFIG_SUB_HASH}"

cd build_unix/

CFLAGS="-Wno-error=implicit-function-declaration" "${BDB_PREFIX}/${BDB_VERSION}/dist/configure" \
  --enable-cxx --disable-shared --disable-replication --with-pic --prefix="${BDB_PREFIX}" \
  "${@}"

make install

echo
echo "db4 build complete."
echo
# shellcheck disable=SC2016
echo 'When compiling pivxd, run `./configure` in the following way:'
echo
echo "  export BDB_PREFIX='${BDB_PREFIX}'"
# shellcheck disable=SC2016
echo '  ./configure BDB_LIBS="-L${BDB_PREFIX}/lib -ldb_cxx-4.8" BDB_CFLAGS="-I${BDB_PREFIX}/include" ...'
